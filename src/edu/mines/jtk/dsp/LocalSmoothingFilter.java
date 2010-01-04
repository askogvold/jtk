/****************************************************************************
Copyright (c) 2008, Colorado School of Mines and others. All rights reserved.
This program and accompanying materials are made available under the terms of
the Common Public License - v1.0, which accompanies this distribution, and is 
available at http://www.eclipse.org/legal/cpl-v10.html
****************************************************************************/
package edu.mines.jtk.dsp;

import java.util.logging.Logger;
import java.util.concurrent.atomic.AtomicInteger;

import edu.mines.jtk.util.AtomicFloat;
import edu.mines.jtk.util.Threads;
import static edu.mines.jtk.util.ArrayMath.*;

/**
 * Local smoothing of images with tensor filter coefficients.
 * Smoothing is performed by solving a sparse symmetric positive-definite
 * (SPD) system of equations: (I+G'DG)y = x, where G is a gradient operator, 
 * D is an SPD tensor field, x is an input image, and y is an output image.
 * <p>
 * The sparse system of filter equations (I+G'DG)y = x is solved iteratively, 
 * beginning with y = x. Iterations continue until either the error in the 
 * solution y is below a specified threshold or the number of iterations 
 * exceeds a specified limit.
 * <p>
 * For low wavenumbers the output of this filter approximates the solution 
 * to an anisotropic inhomogeneous diffusion equation, where the filter 
 * input x corresponds to the initial condition at time t = 0 and filter 
 * output y corresponds to the solution at some later time t.
 * <p>
 * Additional smoothing filters may be applied to the input image x before 
 * or after solving the sparse system of equations for the smoothed output 
 * image y. These additional filters compensate for deficiencies in the 
 * gradient operator G, which is a finite-difference approximation that is 
 * poor for high wavenumbers near the Nyquist limit. The extra smoothing
 * filters attenuate these high wavenumbers.
 * <p> 
 * The additional smoothing filter S is a simple 3x3 (or, in 3D, 3x3x3) 
 * weighted-average filter that zeros Nyquist wavenumbers. This filter 
 * is fast and has non-negative coefficients. However, it may smooth too 
 * much, as it attenuates all non-zero wavenumbers, not only the highest
 * wavenumbers. Moreover, this filter is not isotropic. 
 * <p>
 * The other additional smoothing operator L is an isotropic low-pass 
 * filter designed to pass wavenumbers up to a specified maximum.
 * Although slower than S, the cost of applying L to the input image x is 
 * likely to be insignificant relative to the cost of solving the sparse 
 * system of equations for the output image y.
 *
 * @author Dave Hale, Colorado School of Mines
 * @version 2009.12.31
 */
public class LocalSmoothingFilter {

  /**
   * Constructs a local smoothing filter with default parameters.
   * The default parameter small is 0.01 and the default maximum 
   * number of iterations is 100.
   */
  public LocalSmoothingFilter() {
    this(0.01,100);
  }

  /**
   * Constructs a local smoothing filter with specified iteration parameters.
   * @param small stop when norm of residuals is less than this factor times
   *  the norm of the input array.
   * @param niter stop when number of iterations exceeds this limit.
   */
  public LocalSmoothingFilter(double small, int niter) {
    _small = (float)small;
    _niter = niter;
    _ldk = new LocalDiffusionKernel(LocalDiffusionKernel.Stencil.D71);
  }

  /**
   * Constructs a local smoothing filter with specified parameters.
   * @param small stop when norm of residuals is less than this factor times
   *  the norm of the input array.
   * @param niter stop when number of iterations exceeds this limit.
   * @param ldk local diffusion kernel that computes y += (I+G'DG)x.
   */
  public LocalSmoothingFilter(
    double small, int niter, LocalDiffusionKernel ldk)
  {
    _small = (float)small;
    _niter = niter;
    _ldk = ldk;
  }

  /**
   * Applies this filter for specified constant scale factor.
   * Local smoothing for 1D arrays is a special case that requires no tensors. 
   * All tensors are implicitly scalar values equal to one, so that filtering 
   * is determined entirely by the specified constant scale factor.
   * @param c constant scale factor.
   * @param x input array.
   * @param y output array.
   */
  public void apply(float c, float[] x, float[] y) {
    apply(c,null,x,y);
  }

  /**
   * Applies this filter for specified scale factors.
   * Local smoothing for 1D arrays is a special case that requires no tensors. 
   * All tensors are implicitly scalar values equal to one, so that filtering 
   * is determined entirely by the specified scale factors.
   * @param c constant scale factor.
   * @param s array of scale factors.
   * @param x input array.
   * @param y output array.
   */
  public void apply(float c, float[] s, float[] x, float[] y) {
    int n1 = x.length;

    // Sub-diagonal e of SPD tridiagonal matrix I+G'DG; e[0] = e[n1] = 0.0.
    float[] e = new float[n1+1];
    if (s!=null) {
      c = -0.5f*c;
      for (int i1=1; i1<n1; ++i1)
        e[i1] = c*(s[i1]+s[i1-1]);
    } else {
      c = -c;
      for (int i1=1; i1<n1; ++i1)
        e[i1] = c;
    }

    // Work array w overwrites sub-diagonal array e.
    float[] w = e;

    // Solve tridiagonal system of equations (I+G'DG)y = x.
    float t = 1.0f-e[0]-e[1];
    y[0] = x[0]/t;
    for (int i1=1; i1<n1; ++i1) {
      float di = 1.0f-e[i1]-e[i1+1]; // diagonal element
      float ei = e[i1]; // sub-diagonal element
      w[i1] = ei/t;
      t = di-ei*w[i1];
      y[i1] = (x[i1]-ei*y[i1-1])/t;
    }
    for (int i1=n1-1; i1>0; --i1)
      y[i1-1] -= w[i1]*y[i1];
  }

  /**
   * Applies this filter for specified tensor coefficients.
   * @param d tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(Tensors2 d, float[][] x, float[][] y) 
  {
    apply(d,1.0f,x,y);
  }

  /**
   * Applies this filter for specified tensor coefficients and scale factor.
   * @param d tensor coefficients.
   * @param c constant scale factor for tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(Tensors2 d, float c, float[][] x, float[][] y) {
    apply(d,c,null,x,y);
  }

  /**
   * Applies this filter for specified tensor coefficients and scale factors.
   * @param d tensor coefficients.
   * @param c constant scale factor for tensor coefficients.
   * @param s array of scale factors for tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(
    Tensors2 d, float c, float[][] s, float[][] x, float[][] y) 
  {
    Operator2 a = new LhsOperator2(_ldk,d,c,s);
    scopy(x,y);
    solve(a,x,y);
  }

  /**
   * Applies this filter for specified tensor coefficients.
   * @param d tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(Tensors3 d, float[][][] x, float[][][] y) 
  {
    apply(d,1.0f,x,y);
  }

  /**
   * Applies this filter for specified tensor coefficients and scale factor.
   * @param d tensor coefficients.
   * @param c constant scale factor for tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(Tensors3 d, float c, float[][][] x, float[][][] y) {
    apply(d,c,null,x,y);
  }

  /**
   * Applies this filter for specified tensor coefficients and scale factors.
   * @param d tensor coefficients.
   * @param c constant scale factor for tensor coefficients.
   * @param s array of scale factors for tensor coefficients.
   * @param x input array.
   * @param y output array.
   */
  public void apply(
    Tensors3 d, float c, float[][][] s, float[][][] x, float[][][] y) 
  {
    Operator3 a = new LhsOperator3(_ldk,d,c,s);
    scopy(x,y);
    solve(a,x,y);
  }

  /**
   * Applies a simple 3x3 weighted-average smoothing filter S.
   * Input and output arrays x and y may be the same array.
   * @param x input array.
   * @param y output array.
   */
  public void applySmoothS(float[][] x, float[][] y) {
    smoothS(x,y);
  }

  /**
   * Applies a simple 3x3x3 weighted-average smoothing filter S.
   * Input and output arrays x and y may be the same array.
   * @param x input array.
   * @param y output array.
   */
  public void applySmoothS(float[][][] x, float[][][] y) {
    smoothS(x,y);
  }

  /**
   * Applies an isotropic low-pass smoothing filter L.
   * Input and output arrays x and y may be the same array.
   * @param kmax maximum wavenumber not attenuated, in cycles/sample.
   * @param x input array.
   * @param y output array.
   */
  public void applySmoothL(double kmax, float[][] x, float[][] y) {
    smoothL(kmax,x,y);
  }

  /**
   * Applies an isotropic low-pass smoothing filter L.
   * Input and output arrays x and y may be the same array.
   * @param kmax maximum wavenumber not attenuated, in cycles/sample.
   * @param x input array.
   * @param y output array.
   */
  public void applySmoothL(double kmax, float[][][] x, float[][][] y) {
    smoothL(kmax,x,y);
  }

  ///////////////////////////////////////////////////////////////////////////
  // private

  private static final boolean PARALLEL = true; // false for single-threaded

  private static Logger log = 
    Logger.getLogger(LocalSmoothingFilter.class.getName());

  private float _small; // stop iterations when residuals are small
  private int _niter; // number of iterations
  private LocalDiffusionKernel _ldk; // computes y += (I+G'DG)x
  private BandPassFilter _lpf; // lowpass filter, null until applied
  private double _kmax; // maximum wavenumber for lowpass filter

  /**
   * A symmetric positive-definite operator.
   */
  private static interface Operator2 {
    public void apply(float[][] x, float[][] y);
  }
  private static interface Operator3 {
    public void apply(float[][][] x, float[][][] y);
  }

  private static class LhsOperator2 implements Operator2 {
    LhsOperator2(LocalDiffusionKernel ldk, Tensors2 d, float c, float[][] s) {
      _ldk = ldk;
      _d = d;
      _c = c;
      _s = s;
    }
    public void apply(float[][] x, float[][] y) {
      scopy(x,y);
      _ldk.apply(_d,_c,_s,x,y);
    }
    private LocalDiffusionKernel _ldk;
    private Tensors2 _d;
    private float _c;
    private float[][] _s;
  }

  private static class LhsOperator3 implements Operator3 {
    LhsOperator3(
      LocalDiffusionKernel ldk, Tensors3 d, float c, float[][][] s) 
    {
      _ldk = ldk;
      _d = d;
      _c = c;
      _s = s;
    }
    public void apply(float[][][] x, float[][][] y) {
      scopy(x,y);
      _ldk.apply(_d,_c,_s,x,y);
    }
    private LocalDiffusionKernel _ldk;
    private Tensors3 _d;
    private float _c;
    private float[][][] _s;
  }

  /**
   * Computes y = lowpass(x). Arrays x and y may be the same array.
   */
  private void smoothL(double kmax, float[][] x, float[][] y) {
    ensureLowpassFilter(kmax);
    _lpf.apply(x,y);
  }
  private void smoothL(double kmax, float[][][] x, float[][][] y) {
    ensureLowpassFilter(kmax);
    _lpf.apply(x,y);
  }
  private void ensureLowpassFilter(double kmax) {
    if (_lpf==null || _kmax!=kmax) {
      _kmax = kmax;
      double kdelta = 0.5-kmax;
      double kupper = kmax+0.5*kdelta;
      _lpf = new BandPassFilter(0.0,kupper,kdelta,0.01);
      _lpf.setExtrapolation(BandPassFilter.Extrapolation.ZERO_SLOPE);
      _lpf.setFilterCaching(false);
    }
  }

  /**
   * Computes y = S'Sx. Arrays x and y may be the same array.
   */
  private static void smoothS(float[][] x, float[][] y) {
    int n1 = x[0].length;
    int n2 = x.length;
    float[][] t = new float[2][n1];
    scopy(x[0],t[0]);
    szero(y[0]);
    for (int i2=1,i2m=0; i2<n2; ++i2,++i2m) {
      int j2  = (i2 )%2;
      int j2m = (i2m)%2;
      scopy(x[i2],t[j2]);
      szero(y[i2]);
      float[] x0 = t[j2 ];
      float[] x1 = t[j2m];
      float[] y0 = y[i2 ];
      float[] y1 = y[i2m];
      for (int i1=1,i1m=0; i1<n1; ++i1,++i1m) {
        float x00 = x0[i1 ];
        float x01 = x0[i1m];
        float x10 = x1[i1 ];
        float x11 = x1[i1m];
        //         0.0625 = 1/16
        float xs = 0.0625f*(x00+x01+x10+x11);
        y0[i1 ] += xs;
        y0[i1m] += xs;
        y1[i1 ] += xs;
        y1[i1m] += xs;
      }
    }
  }

  /**
   * Computes y = S'Sx. Arrays x and y may be the same array.
   */
  private static void smoothS(float[][][] x, float[][][] y) {
    int n1 = x[0][0].length;
    int n2 = x[0].length;
    int n3 = x.length;
    float[][][] t = new float[2][n2][n1];
    scopy(x[0],t[0]);
    szero(y[0]);
    for (int i3=1,i3m=0; i3<n3; ++i3,++i3m) {
      int j3  = (i3  )%2;
      int j3m = (i3-1)%2;
      scopy(x[i3],t[j3]);
      szero(y[i3]);
      for (int i2=1,i2m=0; i2<n2; ++i2,++i2m) {
        float[] x00 = t[j3 ][i2 ];
        float[] x01 = t[j3 ][i2m];
        float[] x10 = t[j3m][i2 ];
        float[] x11 = t[j3m][i2m];
        float[] y00 = y[i3 ][i2 ];
        float[] y01 = y[i3 ][i2m];
        float[] y10 = y[i3m][i2 ];
        float[] y11 = y[i3m][i2m];
        for (int i1=1,i1m=0; i1<n1; ++i1,++i1m) {
          float x000 = x00[i1 ];
          float x001 = x00[i1m];
          float x010 = x01[i1 ];
          float x011 = x01[i1m];
          float x100 = x10[i1 ];
          float x101 = x10[i1m];
          float x110 = x11[i1 ];
          float x111 = x11[i1m];
          //         0.015625 = 1/64
          float xs = 0.015625f*(x000+x001+x010+x011+x100+x101+x110+x111);
          y00[i1 ] += xs;
          y00[i1m] += xs;
          y01[i1 ] += xs;
          y01[i1m] += xs;
          y10[i1 ] += xs;
          y10[i1m] += xs;
          y11[i1 ] += xs;
          y11[i1m] += xs;
        }
      }
    }
  }

  /**
   * Solves Ax = b via conjugate gradient iterations. (No preconditioner.)
   * Uses the initial values of x; does not assume they are zero.
   */
  private void solve(Operator2 a, float[][] b, float[][] x) {
    int n1 = b[0].length;
    int n2 = b.length;
    float[][] d = new float[n2][n1];
    float[][] q = new float[n2][n1];
    float[][] r = new float[n2][n1];
    scopy(b,r);
    a.apply(x,q);
    saxpy(-1.0f,q,r); // r = b-Ax
    scopy(r,d);
    float delta = sdot(r,r);
    float deltaBegin = delta;
    float deltaSmall = sdot(b,b)*_small*_small;
    log.fine("solve: delta="+delta);
    int iter;
    for (iter=0; iter<_niter && delta>deltaSmall; ++iter) {
      log.finer("  iter="+iter+" delta="+delta+" ratio="+delta/deltaBegin);
      a.apply(d,q);
      float dq = sdot(d,q);
      float alpha = delta/dq;
      saxpy( alpha,d,x);
      saxpy(-alpha,q,r);
      float deltaOld = delta;
      delta = sdot(r,r);
      float beta = delta/deltaOld;
      sxpay(beta,r,d);
    }
    log.fine("  iter="+iter+" delta="+delta+" ratio="+delta/deltaBegin);
  }
  private void solve(Operator3 a, float[][][] b, float[][][] x) {
    int n1 = b[0][0].length;
    int n2 = b[0].length;
    int n3 = b.length;
    float[][][] d = new float[n3][n2][n1];
    float[][][] q = new float[n3][n2][n1];
    float[][][] r = new float[n3][n2][n1];
    scopy(b,r);
    a.apply(x,q);
    saxpy(-1.0f,q,r); // r = b-Ax
    scopy(r,d);
    float delta = sdot(r,r);
    float deltaBegin = delta;
    float deltaSmall = sdot(b,b)*_small*_small;
    log.fine("solve: delta="+delta);
    int iter;
    for (iter=0; iter<_niter && delta>deltaSmall; ++iter) {
      log.finer("  iter="+iter+" delta="+delta+" ratio="+delta/deltaBegin);
      a.apply(d,q);
      float dq = sdot(d,q);
      float alpha = delta/dq;
      saxpy( alpha,d,x);
      saxpy(-alpha,q,r);
      float deltaOld = delta;
      delta = sdot(r,r);
      float beta = delta/deltaOld;
      sxpay(beta,r,d);
    }
    log.fine("  iter="+iter+" delta="+delta+" ratio="+delta/deltaBegin);
  }

  // Zeros array x.
  private static void szero(float[] x) {
    zero(x);
  }
  private static void szero(float[][] x) {
    zero(x);
  }
  private static void szero(float[][][] x) {
    if (PARALLEL) {
      szeroP(x);
    } else {
      szeroS(x);
    }
  }
  private static void szeroS(float[][][] x) {
    int n3 = x.length;
    for (int i3=0; i3<n3; ++i3)
      szero(x[i3]);
  }
  private static void szeroP(final float[][][] x) {
    final int n3 = x.length;
    final AtomicInteger a3 = new AtomicInteger(0);
    Thread[] threads = Threads.makeArray();
    for (int ithread=0; ithread<threads.length; ++ithread) {
      threads[ithread] = new Thread(new Runnable() {
        public void run() {
          for (int i3=a3.getAndIncrement(); i3<n3; i3=a3.getAndIncrement())
            szero(x[i3]);
        }
      });
    }
    Threads.startAndJoin(threads);
  }

  // Copys array x to array y.
  private static void scopy(float[] x, float[] y) {
    copy(x,y);
  }
  private static void scopy(float[][] x, float[][] y) {
    copy(x,y);
  }
  private static void scopy(float[][][] x, float[][][] y) {
    if (PARALLEL) {
      scopyP(x,y);
    } else {
      scopyS(x,y);
    }
  }
  private static void scopyS(float[][][] x, float[][][] y) {
    int n3 = x.length;
    for (int i3=0; i3<n3; ++i3)
      scopy(x[i3],y[i3]);
  }
  private static void scopyP(final float[][][] x, final float[][][] y) {
    final int n3 = x.length;
    final AtomicInteger a3 = new AtomicInteger(0);
    Thread[] threads = Threads.makeArray();
    for (int ithread=0; ithread<threads.length; ++ithread) {
      threads[ithread] = new Thread(new Runnable() {
        public void run() {
          for (int i3=a3.getAndIncrement(); i3<n3; i3=a3.getAndIncrement())
            scopy(x[i3],y[i3]);
        }
      });
    }
    Threads.startAndJoin(threads);
  }

  // Returns the dot product x'y.
  private static float sdot(float[][] x, float[][] y) {
    int n1 = x[0].length;
    int n2 = x.length;
    float d = 0.0f;
    for (int i2=0; i2<n2; ++i2) {
      float[] x2 = x[i2], y2 = y[i2];
      for (int i1=0; i1<n1; ++i1) {
        d += x2[i1]*y2[i1];
      }
    }
    return d;
  }
  private static float sdot(float[][][] x, float[][][] y) {
    if (PARALLEL) {
      return sdotP(x,y);
    } else {
      return sdotS(x,y);
    }
  }
  private static float sdotS(float[][][] x, float[][][] y) {
    int n3 = x.length;
    float d = 0.0f;
    for (int i3=0; i3<n3; ++i3)
      d += sdot(x[i3],y[i3]);
    return d;
  }
  private static float sdotP(final float[][][] x, final float[][][] y) {
    final int n3 = x.length;
    final AtomicFloat ad = new AtomicFloat(0.0f);
    final AtomicInteger a3 = new AtomicInteger(0);
    Thread[] threads = Threads.makeArray();
    for (int ithread=0; ithread<threads.length; ++ithread) {
      threads[ithread] = new Thread(new Runnable() {
        public void run() {
          float d = 0.0f;
          for (int i3=a3.getAndIncrement(); i3<n3; i3=a3.getAndIncrement())
            d += sdot(x[i3],y[i3]);
          ad.getAndAdd(d);
        }
      });
    }
    Threads.startAndJoin(threads);
    return ad.get();
  }

  // Computes y = y + a*x.
  private static void saxpy(float a, float[][] x, float[][] y) {
    int n1 = x[0].length;
    int n2 = x.length;
    for (int i2=0; i2<n2; ++i2) {
      float[] x2 = x[i2], y2 = y[i2];
      for (int i1=0; i1<n1; ++i1) {
        y2[i1] += a*x2[i1];
      }
    }
  }
  private static void saxpy(float a, float[][][] x, float[][][] y) {
    if (PARALLEL) {
      saxpyP(a,x,y);
    } else {
      saxpyS(a,x,y);
    }
  }
  private static void saxpyS(float a, float[][][] x, float[][][] y) {
    int n3 = x.length;
    for (int i3=0; i3<n3; ++i3)
      saxpy(a,x[i3],y[i3]);
  }
  private static void saxpyP(
    final float a, final float[][][] x, final float[][][] y)
  {
    final int n3 = x.length;
    final AtomicInteger a3 = new AtomicInteger(0);
    Thread[] threads = Threads.makeArray();
    for (int ithread=0; ithread<threads.length; ++ithread) {
      threads[ithread] = new Thread(new Runnable() {
        public void run() {
          for (int i3=a3.getAndIncrement(); i3<n3; i3=a3.getAndIncrement())
            saxpy(a,x[i3],y[i3]);
        }
      });
    }
    Threads.startAndJoin(threads);
  }

  // Computes y = x + a*y.
  private static void sxpay(float a, float[][] x, float[][] y) {
    int n1 = x[0].length;
    int n2 = x.length;
    for (int i2=0; i2<n2; ++i2) {
      float[] x2 = x[i2], y2 = y[i2];
      for (int i1=0; i1<n1; ++i1) {
        y2[i1] = a*y2[i1]+x2[i1];
      }
    }
  }
  private static void sxpay(float a, float[][][] x, float[][][] y) {
    if (PARALLEL) {
      sxpayP(a,x,y);
    } else {
      sxpayS(a,x,y);
    }
  }
  private static void sxpayS(float a, float[][][] x, float[][][] y) {
    int n3 = x.length;
    for (int i3=0; i3<n3; ++i3)
      sxpay(a,x[i3],y[i3]);
  }
  private static void sxpayP(
    final float a, final float[][][] x, final float[][][] y)
  {
    final int n3 = x.length;
    final AtomicInteger a3 = new AtomicInteger(0);
    Thread[] threads = Threads.makeArray();
    for (int ithread=0; ithread<threads.length; ++ithread) {
      threads[ithread] = new Thread(new Runnable() {
        public void run() {
          for (int i3=a3.getAndIncrement(); i3<n3; i3=a3.getAndIncrement())
            sxpay(a,x[i3],y[i3]);
        }
      });
    }
    Threads.startAndJoin(threads);
  }
}
