/****************************************************************************
Copyright (c) 2004, Colorado School of Mines and others. All rights reserved.
This program and accompanying materials are made available under the terms of
the Common Public License - v1.0, which accompanies this distribution, and is
available at http://www.eclipse.org/legal/cpl-v10.html
****************************************************************************/

/****************************************************************************
Gl JNI glue.
@author Dave Hale, Colorado School of Mines
****************************************************************************/
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#include "../util/jniglue.h"

#define JNI_GL_DECLARE0(name) extern "C" JNIEXPORT void JNICALL \
Java_edu_mines_jves_opengl_Gl_##name(\
  JNIEnv* env, jclass cls)
#define JNI_GL_DECLARE1(name) extern "C" JNIEXPORT void JNICALL \
Java_edu_mines_jves_opengl_Gl_##name(\
  JNIEnv* env, jclass cls,
#define JNI_GL_DECLARE2(name) extern "C" JNIEXPORT void JNICALL \
Java_edu_mines_jves_opengl_Gl_n##name(\
  JNIEnv* env, jclass cls, jlong pfunc,
#define JNI_GL_DECLARE_RETURN0(type,name) extern "C" JNIEXPORT type JNICALL \
Java_edu_mines_jves_opengl_Gl_##name(\
  JNIEnv* env, jclass cls)
#define JNI_GL_DECLARE_RETURN1(type,name) extern "C" JNIEXPORT type JNICALL \
Java_edu_mines_jves_opengl_Gl_##name(\
  JNIEnv* env, jclass cls,
#define JNI_GL_BEGIN0 {\
  JNI_TRY
#define JNI_GL_BEGIN1 ) {\
  JNI_TRY
#define JNI_GL_BEGIN2 ) {\
  JNI_TRY
#define JNI_GL_END JNI_CATCH \
}

JNI_GL_DECLARE1(glAccum)
  jint op, jfloat value
JNI_GL_BEGIN1
  glAccum(op,value);
JNI_GL_END

JNI_GL_DECLARE1(glAlphaFunc)
  jint func, jfloat ref
JNI_GL_BEGIN1
  glAlphaFunc(func,ref);
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jboolean,glAreTexturesResident)
  jint n, jintArray jtextures, jbyteArray jresidences
JNI_GL_BEGIN1
  JuintArray textures(env,jtextures);
  JubyteArray residences(env,jresidences);
  return (glAreTexturesResident(n,textures,residences)==GL_TRUE) ?
    JNI_TRUE :
    JNI_FALSE;
JNI_GL_END

JNI_GL_DECLARE1(glArrayElement)
  jint i
JNI_GL_BEGIN1
  glArrayElement(i);
JNI_GL_END

JNI_GL_DECLARE1(glBegin)
  jint mode
JNI_GL_BEGIN1
  glBegin(mode);
JNI_GL_END

JNI_GL_DECLARE1(glBindTexture)
  jint target, jint texture
JNI_GL_BEGIN1
  glBindTexture(target,texture);
JNI_GL_END

JNI_GL_DECLARE1(glBitmap)
  jint width, jint height, jfloat xorig, jfloat yorig,
  jfloat xmove, jfloat ymove, jbyteArray jbitmap
JNI_GL_BEGIN1
  JubyteArray bitmap(env,jbitmap);
  glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap);
JNI_GL_END

JNI_GL_DECLARE1(glBlendFunc)
  jint sfactor, jint dfactor
JNI_GL_BEGIN1
  glBlendFunc(sfactor,dfactor);
JNI_GL_END

JNI_GL_DECLARE1(glCallList)
  jint list
JNI_GL_BEGIN1
  glCallList(list);
JNI_GL_END

/*
Z boolean
B byte
C char
S short
I int
J long
F float
D double
_3Z boolean[]
_3B byte[]
...
*/

JNI_GL_DECLARE1(glCallLists__II_3B)
  jint n, jint type, jbyteArray jlists
JNI_GL_BEGIN1
  JvoidArray lists(env,jlists);
  glCallLists(n,type,lists);
JNI_GL_END

JNI_GL_DECLARE1(glCallLists__II_3I)
  jint n, jint type, jintArray jlists
JNI_GL_BEGIN1
  JvoidArray lists(env,jlists);
  glCallLists(n,type,lists);
JNI_GL_END

JNI_GL_DECLARE1(glCallLists__II_3S)
  jint n, jint type, jshortArray jlists
JNI_GL_BEGIN1
  JvoidArray lists(env,jlists);
  glCallLists(n,type,lists);
JNI_GL_END

JNI_GL_DECLARE1(glClear)
  jint mask
JNI_GL_BEGIN1
  glClear(mask);
JNI_GL_END

JNI_GL_DECLARE1(glClearAccum)
  jfloat red, jfloat green, jfloat blue, jfloat alpha
JNI_GL_BEGIN1
  glClearAccum(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glClearColor)
  jfloat red, jfloat green, jfloat blue, jfloat alpha
JNI_GL_BEGIN1
  glClearColor(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glClearDepth)
  jdouble depth
JNI_GL_BEGIN1
  glClearDepth(depth);
JNI_GL_END

JNI_GL_DECLARE1(glClearIndex)
  jfloat c
JNI_GL_BEGIN1
  glClearIndex(c);
JNI_GL_END

JNI_GL_DECLARE1(glClearStencil)
  jint s
JNI_GL_BEGIN1
  glClearStencil(s);
JNI_GL_END

JNI_GL_DECLARE1(glClipPlane)
  jint plane, jdoubleArray jequation
JNI_GL_BEGIN1
  JdoubleArray equation(env,jequation);
  glClipPlane(plane,equation);
JNI_GL_END

JNI_GL_DECLARE1(glColor3b)
  jbyte red, jbyte green, jbyte blue
JNI_GL_BEGIN1
  glColor3b(red,green,blue);
JNI_GL_END

JNI_GL_DECLARE1(glColor3bv)
  jbyteArray jv
JNI_GL_BEGIN1
  JbyteArray v(env,jv);
  glColor3bv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor3d)
  jdouble red, jdouble green, jdouble blue
JNI_GL_BEGIN1
  glColor3d(red,green,blue);
JNI_GL_END

JNI_GL_DECLARE1(glColor3dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glColor3dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor3f)
  jfloat red, jfloat green, jfloat blue
JNI_GL_BEGIN1
  glColor3f(red,green,blue);
JNI_GL_END

JNI_GL_DECLARE1(glColor3fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glColor3fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor3i)
  jint red, jint green, jint blue
JNI_GL_BEGIN1
  glColor3i(red,green,blue);
JNI_GL_END

JNI_GL_DECLARE1(glColor3iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glColor3iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor3s)
  jshort red, jshort green, jshort blue
JNI_GL_BEGIN1
  glColor3s(red,green,blue);
JNI_GL_END

JNI_GL_DECLARE1(glColor3sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glColor3sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor4b)
  jbyte red, jbyte green, jbyte blue, jbyte alpha
JNI_GL_BEGIN1
  glColor4b(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColor4bv)
  jbyteArray jv
JNI_GL_BEGIN1
  JbyteArray v(env,jv);
  glColor4bv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor4d)
  jdouble red, jdouble green, jdouble blue, jdouble alpha
JNI_GL_BEGIN1
  glColor4d(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColor4dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glColor4dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor4f)
  jfloat red, jfloat green, jfloat blue, jfloat alpha
JNI_GL_BEGIN1
  glColor4f(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColor4fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glColor4fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor4i)
  jint red, jint green, jint blue, jint alpha
JNI_GL_BEGIN1
  glColor4i(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColor4iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glColor4iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColor4s)
  jshort red, jshort green, jshort blue, jshort alpha
JNI_GL_BEGIN1
  glColor4s(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColor4sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glColor4sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glColorMask)
  jbyte red, jbyte green, jbyte blue, jbyte alpha
JNI_GL_BEGIN1
  glColorMask(red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE1(glColorMaterial)
  jint face, jint mode
JNI_GL_BEGIN1
  glColorMaterial(face,mode);
JNI_GL_END

JNI_GL_DECLARE1(glColorPointer)
  jint size, jint type, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glColorPointer(size,type,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glCopyPixels)
  jint x, jint y, jint width, jint height, jint type
JNI_GL_BEGIN1
  glCopyPixels(x,y,width,height,type);
JNI_GL_END

JNI_GL_DECLARE1(glCopyTexImage1D)
  jint target, jint level, jint internalFormat, 
  jint x, jint y, jint width, jint border
JNI_GL_BEGIN1
  glCopyTexImage1D(target,level,internalFormat,x,y,width,border);
JNI_GL_END

JNI_GL_DECLARE1(glCopyTexImage2D)
  jint target, jint level, jint internalFormat, 
  jint x, jint y, jint width, jint height, jint border
JNI_GL_BEGIN1
  glCopyTexImage2D(target,level,internalFormat,x,y,width,height,border);
JNI_GL_END

JNI_GL_DECLARE1(glCopyTexSubImage1D)
  jint target, jint level, jint xoffset, jint x, jint y, jint width
JNI_GL_BEGIN1
  glCopyTexSubImage1D(target,level,xoffset,x,y,width);
JNI_GL_END

JNI_GL_DECLARE1(glCopyTexSubImage2D)
  jint target, jint level, jint xoffset, jint yoffset,
  jint x, jint y, jint width, jint height
JNI_GL_BEGIN1
  glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);
JNI_GL_END

JNI_GL_DECLARE1(glCullFace)
  jint mode
JNI_GL_BEGIN1
  glCullFace(mode);
JNI_GL_END

JNI_GL_DECLARE1(glDeleteLists)
  jint list, jint range
JNI_GL_BEGIN1
  glDeleteLists(list,range);
JNI_GL_END

JNI_GL_DECLARE1(glDeleteTextures)
  jint n, jintArray jtextures
JNI_GL_BEGIN1
  JuintArray textures(env,jtextures);
  glDeleteTextures(n,textures);
JNI_GL_END

JNI_GL_DECLARE1(glDepthFunc)
  jint func
JNI_GL_BEGIN1
  glDepthFunc(func);
JNI_GL_END

JNI_GL_DECLARE1(glDepthMask)
  jbyte flag
JNI_GL_BEGIN1
  glDepthMask(flag);
JNI_GL_END

JNI_GL_DECLARE1(glDepthRange)
  jdouble zNear, jdouble zFar
JNI_GL_BEGIN1
  glDepthRange(zNear,zFar);
JNI_GL_END

JNI_GL_DECLARE1(glDisable)
  jint cap
JNI_GL_BEGIN1
  glDisable(cap);
JNI_GL_END

JNI_GL_DECLARE1(glDisableClientState)
  jint array
JNI_GL_BEGIN1
  glDisableClientState(array);
JNI_GL_END

JNI_GL_DECLARE1(glDrawArrays)
  jint mode, jint first, jint count
JNI_GL_BEGIN1
  glDrawArrays(mode,first,count);
JNI_GL_END

JNI_GL_DECLARE1(glDrawBuffer)
  jint mode
JNI_GL_BEGIN1
  glDrawBuffer(mode);
JNI_GL_END

JNI_GL_DECLARE1(glDrawElements__III_3B)
  jint mode, jint count, jint type, jarray jindices
JNI_GL_BEGIN1
  JvoidArray indices(env,jindices);
  glDrawElements(mode,count,type,indices);
JNI_GL_END

JNI_GL_DECLARE1(glDrawElements__III_3I)
  jint mode, jint count, jint type, jarray jindices
JNI_GL_BEGIN1
  JvoidArray indices(env,jindices);
  glDrawElements(mode,count,type,indices);
JNI_GL_END

JNI_GL_DECLARE1(glDrawElements__III_3S)
  jint mode, jint count, jint type, jarray jindices
JNI_GL_BEGIN1
  JvoidArray indices(env,jindices);
  glDrawElements(mode,count,type,indices);
JNI_GL_END

JNI_GL_DECLARE1(glDrawPixels__IIII_3B)
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glDrawPixels(width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glDrawPixels__IIII_3I)
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glDrawPixels(width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glDrawPixels__IIII_3S)
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glDrawPixels(width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glEdgeFlag)
  jbyte flag
JNI_GL_BEGIN1
  glEdgeFlag(flag);
JNI_GL_END

JNI_GL_DECLARE1(glEdgeFlagPointer)
  jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glEdgeFlagPointer(stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glEdgeFlagv)
  jbyteArray jflag
JNI_GL_BEGIN1
  JubyteArray flag(env,jflag);
  glEdgeFlagv(flag);
JNI_GL_END

JNI_GL_DECLARE1(glEnable)
  jint cap
JNI_GL_BEGIN1
  glEnable(cap);
JNI_GL_END

JNI_GL_DECLARE1(glEnableClientState)
  jint array
JNI_GL_BEGIN1
  glEnableClientState(array);
JNI_GL_END

JNI_GL_DECLARE0(glEnd)
JNI_GL_BEGIN0
  glEnd();
JNI_GL_END

JNI_GL_DECLARE0(glEndList)
JNI_GL_BEGIN0
  glEndList();
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord1d)
  jdouble u
JNI_GL_BEGIN1
  glEvalCoord1d(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord1dv)
  jdoubleArray ju
JNI_GL_BEGIN1
  JdoubleArray u(env,ju);
  glEvalCoord1dv(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord1f)
  jfloat u
JNI_GL_BEGIN1
  glEvalCoord1f(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord1fv)
  jfloatArray ju
JNI_GL_BEGIN1
  JfloatArray u(env,ju);
  glEvalCoord1fv(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord2d)
  jdouble u, jdouble v
JNI_GL_BEGIN1
  glEvalCoord2d(u,v);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord2dv)
  jdoubleArray ju
JNI_GL_BEGIN1
  JdoubleArray u(env,ju);
  glEvalCoord2dv(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord2f)
  jfloat u, jfloat v
JNI_GL_BEGIN1
  glEvalCoord2f(u,v);
JNI_GL_END

JNI_GL_DECLARE1(glEvalCoord2fv)
  jfloatArray ju
JNI_GL_BEGIN1
  JfloatArray u(env,ju);
  glEvalCoord2fv(u);
JNI_GL_END

JNI_GL_DECLARE1(glEvalMesh1)
  jint mode, jint i1, jint i2
JNI_GL_BEGIN1
  glEvalMesh1(mode,i1,i2);
JNI_GL_END

JNI_GL_DECLARE1(glEvalMesh2)
  jint mode, jint i1, jint i2, jint j1, jint j2
JNI_GL_BEGIN1
  glEvalMesh2(mode,i1,i2,j1,j2);
JNI_GL_END

JNI_GL_DECLARE1(glEvalPoint1)
  jint i
JNI_GL_BEGIN1
  glEvalPoint1(i);
JNI_GL_END

JNI_GL_DECLARE1(glEvalPoint2)
  jint i, jint j
JNI_GL_BEGIN1
  glEvalPoint2(i,j);
JNI_GL_END

JNI_GL_DECLARE1(glFeedbackBuffer)
  jint size, jint type, jobject jbuffer
JNI_GL_BEGIN1
  JfloatBuffer buffer(env,jbuffer);
  glFeedbackBuffer(size,type,buffer);
JNI_GL_END

JNI_GL_DECLARE0(glFinish)
JNI_GL_BEGIN0
  glFinish();
JNI_GL_END

JNI_GL_DECLARE0(glFlush)
JNI_GL_BEGIN0
  glFlush();
JNI_GL_END

JNI_GL_DECLARE1(glFogf)
  jint pname, jfloat param
JNI_GL_BEGIN1
  glFogf(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glFogfv)
  jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glFogfv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glFogi)
  jint pname, jint param
JNI_GL_BEGIN1
  glFogi(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glFogiv)
  jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glFogiv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glFrontFace)
  jint mode
JNI_GL_BEGIN1
  glFrontFace(mode);
JNI_GL_END

JNI_GL_DECLARE1(glFrustum)
  jdouble left, jdouble right,
  jdouble bottom, jdouble top,
  jdouble zNear, jdouble zFar
JNI_GL_BEGIN1
  glFrustum(left,right,bottom,top,zNear,zFar);
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jint,glGenLists)
  jint range
JNI_GL_BEGIN1
  return glGenLists(range);
JNI_GL_END

JNI_GL_DECLARE1(glGenTextures)
  jint n, jintArray jtextures
JNI_GL_BEGIN1
  JuintArray textures(env,jtextures);
  glGenTextures(n,textures);
JNI_GL_END

JNI_GL_DECLARE1(glGetBooleanv)
  jint pname, jbyteArray jparams
JNI_GL_BEGIN1
  JubyteArray params(env,jparams);
  glGetBooleanv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetClipPlane)
  jint plane, jdoubleArray jequation
JNI_GL_BEGIN1
  JdoubleArray equation(env,jequation);
  glGetClipPlane(plane,equation);
JNI_GL_END

JNI_GL_DECLARE1(glGetDoublev)
  jint pname, jdoubleArray jparams
JNI_GL_BEGIN1
  JdoubleArray params(env,jparams);
  glGetDoublev(pname,params);
JNI_GL_END

JNI_GL_DECLARE_RETURN0(jint,glGetError)
JNI_GL_BEGIN0
  return glGetError();
JNI_GL_END

JNI_GL_DECLARE1(glGetFloatv)
  jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetFloatv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetIntegerv)
  jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetIntegerv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetLightfv)
  jint light, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetLightfv(light,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetLightiv)
  jint light, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetLightiv(light,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetMapdv)
  jint target, jint query, jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glGetMapdv(target,query,v);
JNI_GL_END

JNI_GL_DECLARE1(glGetMapfv)
  jint target, jint query, jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glGetMapfv(target,query,v);
JNI_GL_END

JNI_GL_DECLARE1(glGetMapiv)
  jint target, jint query, jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glGetMapiv(target,query,v);
JNI_GL_END

JNI_GL_DECLARE1(glGetMaterialfv)
  jint face, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetMaterialfv(face,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetMaterialiv)
  jint face, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetMaterialiv(face,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetPixelMapfv)
  jint map, jfloatArray jvalues
JNI_GL_BEGIN1
  JfloatArray values(env,jvalues);
  glGetPixelMapfv(map,values);
JNI_GL_END

JNI_GL_DECLARE1(glGetPixelMapuiv)
  jint map, jintArray jvalues
JNI_GL_BEGIN1
  JuintArray values(env,jvalues);
  glGetPixelMapuiv(map,values);
JNI_GL_END

JNI_GL_DECLARE1(glGetPixelMapusv)
  jint map, jshortArray jvalues
JNI_GL_BEGIN1
  JushortArray values(env,jvalues);
  glGetPixelMapusv(map,values);
JNI_GL_END

JNI_GL_DECLARE1(glGetPolygonStipple)
  jbyteArray jmask
JNI_GL_BEGIN1
  JubyteArray mask(env,jmask);
  glGetPolygonStipple(mask);
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jstring,glGetString)
  int name
JNI_GL_BEGIN1
  return env->NewStringUTF((const char*)glGetString(name));
JNI_GL_END

JNI_GL_DECLARE1(glGetTexEnvfv)
  jint target, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetTexEnvfv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexEnviv)
  jint target, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetTexEnviv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexGendv)
  jint coord, jint pname, jdoubleArray jparams
JNI_GL_BEGIN1
  JdoubleArray params(env,jparams);
  glGetTexGendv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexGenfv)
  jint coord, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetTexGenfv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexGeniv)
  jint coord, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetTexGeniv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexImage__IIII_3B)
  jint target, jint level, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glGetTexImage(target,level,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexImage__IIII_3I)
  jint target, jint level, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glGetTexImage(target,level,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexImage__IIII_3S)
  jint target, jint level, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glGetTexImage(target,level,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexLevelParameterfv)
  jint target, jint level, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetTexLevelParameterfv(target,level,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexLevelParameteriv)
  jint target, jint level, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetTexLevelParameteriv(target,level,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexParameterfv)
  jint target, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glGetTexParameterfv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glGetTexParameteriv)
  jint target, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glGetTexParameteriv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glHint)
  jint target, jint mode
JNI_GL_BEGIN1
  glHint(target,mode);
JNI_GL_END

JNI_GL_DECLARE1(glIndexMask)
  jint mask
JNI_GL_BEGIN1
  glIndexMask(mask);
JNI_GL_END

JNI_GL_DECLARE1(glIndexPointer)
  jint type, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glIndexPointer(type,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glIndexd)
  jdouble c
JNI_GL_BEGIN1
  glIndexd(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexdv)
  jdoubleArray jc
JNI_GL_BEGIN1
  JdoubleArray c(env,jc);
  glIndexdv(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexf)
  jfloat c
JNI_GL_BEGIN1
  glIndexf(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexfv)
  jfloatArray jc
JNI_GL_BEGIN1
  JfloatArray c(env,jc);
  glIndexfv(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexi)
  jint c
JNI_GL_BEGIN1
  glIndexi(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexiv)
  jintArray jc
JNI_GL_BEGIN1
  JintArray c(env,jc);
  glIndexiv(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexs)
  jshort c
JNI_GL_BEGIN1
  glIndexs(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexsv)
  jshortArray jc
JNI_GL_BEGIN1
  JshortArray c(env,jc);
  glIndexsv(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexub)
  jbyte c
JNI_GL_BEGIN1
  glIndexub(c);
JNI_GL_END

JNI_GL_DECLARE1(glIndexubv)
  jbyteArray jc
JNI_GL_BEGIN1
  JubyteArray c(env,jc);
  glIndexubv(c);
JNI_GL_END

JNI_GL_DECLARE0(glInitNames)
JNI_GL_BEGIN0
  glInitNames();
JNI_GL_END

JNI_GL_DECLARE1(glInterleavedArrays)
  jint format, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glInterleavedArrays(format,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jboolean,glIsEnabled)
  jint cap
JNI_GL_BEGIN1
  return (glIsEnabled(cap)==GL_TRUE)?JNI_TRUE:JNI_FALSE;
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jboolean,glIsList)
  jint list
JNI_GL_BEGIN1
  return (glIsList(list)==GL_TRUE)?JNI_TRUE:JNI_FALSE;
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jboolean,glIsTexture)
  jint texture
JNI_GL_BEGIN1
  return (glIsTexture(texture)==GL_TRUE)?JNI_TRUE:JNI_FALSE;
JNI_GL_END

JNI_GL_DECLARE1(glLightModelf)
  jint pname, jfloat param
JNI_GL_BEGIN1
  glLightModelf(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glLightModelfv)
  jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glLightModelfv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glLightModeli)
  jint pname, jint param
JNI_GL_BEGIN1
  glLightModeli(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glLightModeliv)
  jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glLightModeliv(pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glLightf)
  jint light, jint pname, jfloat param
JNI_GL_BEGIN1
  glLightf(light,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glLightfv)
  jint light, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glLightfv(light,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glLighti)
  jint light, jint pname, jint param
JNI_GL_BEGIN1
  glLighti(light,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glLightiv)
  jint light, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glLightiv(light,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glLineStipple)
  jint factor, jshort pattern
JNI_GL_BEGIN1
  glLineStipple(factor,pattern);
JNI_GL_END

JNI_GL_DECLARE1(glLineWidth)
  jfloat width
JNI_GL_BEGIN1
  glLineWidth(width);
JNI_GL_END

JNI_GL_DECLARE1(glListBase)
  jint base
JNI_GL_BEGIN1
  glListBase(base);
JNI_GL_END

JNI_GL_DECLARE0(glLoadIdentity)
JNI_GL_BEGIN0
  glLoadIdentity();
JNI_GL_END

JNI_GL_DECLARE1(glLoadMatrixd)
  jdoubleArray jm
JNI_GL_BEGIN1
  JdoubleArray m(env,jm);
  glLoadMatrixd(m);
JNI_GL_END

JNI_GL_DECLARE1(glLoadMatrixf)
  jfloatArray jm
JNI_GL_BEGIN1
  JfloatArray m(env,jm);
  glLoadMatrixf(m);
JNI_GL_END

JNI_GL_DECLARE1(glLoadName)
  jint name
JNI_GL_BEGIN1
  glLoadName(name);
JNI_GL_END

JNI_GL_DECLARE1(glLogicOp)
  jint opcode
JNI_GL_BEGIN1
  glLogicOp(opcode);
JNI_GL_END

JNI_GL_DECLARE1(glMap1d)
  jint target, 
  jdouble u1, jdouble u2, jint stride, jint order, 
  jdoubleArray jpoints
JNI_GL_BEGIN1
  JdoubleArray points(env,jpoints);
  glMap1d(target,u1,u2,stride,order,points);
JNI_GL_END

JNI_GL_DECLARE1(glMap1f)
  jint target, 
  jfloat u1, jfloat u2, jint stride, jint order, 
  jfloatArray jpoints
JNI_GL_BEGIN1
  JfloatArray points(env,jpoints);
  glMap1f(target,u1,u2,stride,order,points);
JNI_GL_END

JNI_GL_DECLARE1(glMap2d)
  jint target, 
  jdouble u1, jdouble u2, jint ustride, jint uorder, 
  jdouble v1, jdouble v2, jint vstride, jint vorder, 
  jdoubleArray jpoints
JNI_GL_BEGIN1
  JdoubleArray points(env,jpoints);
  glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
JNI_GL_END

JNI_GL_DECLARE1(glMap2f)
  jint target, 
  jfloat u1, jfloat u2, jint ustride, jint uorder, 
  jfloat v1, jfloat v2, jint vstride, jint vorder, 
  jfloatArray jpoints
JNI_GL_BEGIN1
  JfloatArray points(env,jpoints);
  glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
JNI_GL_END

JNI_GL_DECLARE1(glMapGrid1d)
  jint un, jdouble u1, jdouble u2 
JNI_GL_BEGIN1
  glMapGrid1d(un,u1,u2);
JNI_GL_END

JNI_GL_DECLARE1(glMapGrid1f)
  jint un, jfloat u1, jfloat u2 
JNI_GL_BEGIN1
  glMapGrid1f(un,u1,u2);
JNI_GL_END

JNI_GL_DECLARE1(glMapGrid2d)
  jint un, jdouble u1, jdouble u2,
  jint vn, jdouble v1, jdouble v2
JNI_GL_BEGIN1
  glMapGrid2d(un,u1,u2,vn,v1,v2);
JNI_GL_END

JNI_GL_DECLARE1(glMapGrid2f)
  jint un, jfloat u1, jfloat u2,
  jint vn, jfloat v1, jfloat v2
JNI_GL_BEGIN1
  glMapGrid2f(un,u1,u2,vn,v1,v2);
JNI_GL_END

JNI_GL_DECLARE1(glMaterialf)
  jint face, jint pname, jfloat param
JNI_GL_BEGIN1
  glMaterialf(face,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glMaterialfv)
  jint face, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glMaterialfv(face,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glMateriali)
  jint face, jint pname, jint param
JNI_GL_BEGIN1
  glMateriali(face,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glMaterialiv)
  jint face, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glMaterialiv(face,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glMatrixMode)
  jint mode
JNI_GL_BEGIN1
  glMatrixMode(mode);
JNI_GL_END

JNI_GL_DECLARE1(glMultMatrixd)
  jdoubleArray jm
JNI_GL_BEGIN1
  JdoubleArray m(env,jm);
  glMultMatrixd(m);
JNI_GL_END

JNI_GL_DECLARE1(glMultMatrixf)
  jfloatArray jm
JNI_GL_BEGIN1
  JfloatArray m(env,jm);
  glMultMatrixf(m);
JNI_GL_END

JNI_GL_DECLARE1(glNewList)
  jint list, jint mode
JNI_GL_BEGIN1
  glNewList(list,mode);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3b)
  jbyte nx, jbyte ny, jbyte nz
JNI_GL_BEGIN1
  glNormal3b(nx,ny,nz);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3bv)
  jbyteArray jv
JNI_GL_BEGIN1
  JbyteArray v(env,jv);
  glNormal3bv(v);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3d)
  jdouble nx, jdouble ny, jdouble nz
JNI_GL_BEGIN1
  glNormal3d(nx,ny,nz);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glNormal3dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3f)
  jfloat nx, jfloat ny, jfloat nz
JNI_GL_BEGIN1
  glNormal3f(nx,ny,nz);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glNormal3fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3i)
  jint nx, jint ny, jint nz
JNI_GL_BEGIN1
  glNormal3i(nx,ny,nz);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glNormal3iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3s)
  jshort nx, jshort ny, jshort nz
JNI_GL_BEGIN1
  glNormal3s(nx,ny,nz);
JNI_GL_END

JNI_GL_DECLARE1(glNormal3sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glNormal3sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glNormalPointer)
  jint type, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glNormalPointer(type,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glOrtho)
  jdouble left, jdouble right,
  jdouble bottom, jdouble top,
  jdouble zNear, jdouble zFar
JNI_GL_BEGIN1
  glOrtho(left,right,bottom,top,zNear,zFar);
JNI_GL_END

JNI_GL_DECLARE1(glPassThrough)
  jfloat token
JNI_GL_BEGIN1
  glPassThrough(token);
JNI_GL_END

JNI_GL_DECLARE1(glPixelMapfv)
  jint map, jint mapsize, jfloatArray jvalues
JNI_GL_BEGIN1
  JfloatArray values(env,jvalues);
  glPixelMapfv(map,mapsize,values);
JNI_GL_END

JNI_GL_DECLARE1(glPixelMapuiv)
  jint map, jint mapsize, jintArray jvalues
JNI_GL_BEGIN1
  JuintArray values(env,jvalues);
  glPixelMapuiv(map,mapsize,values);
JNI_GL_END

JNI_GL_DECLARE1(glPixelMapusv)
  jint map, jint mapsize, jshortArray jvalues
JNI_GL_BEGIN1
  JushortArray values(env,jvalues);
  glPixelMapusv(map,mapsize,values);
JNI_GL_END

JNI_GL_DECLARE1(glPixelStoref)
  jint pname, jfloat param
JNI_GL_BEGIN1
  glPixelStoref(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glPixelStorei)
  jint pname, jint param
JNI_GL_BEGIN1
  glPixelStorei(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glPixelTransferf)
  jint pname, jfloat param
JNI_GL_BEGIN1
  glPixelTransferf(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glPixelTransferi)
  jint pname, jint param
JNI_GL_BEGIN1
  glPixelTransferi(pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glPixelZoom)
  jfloat xfactor, jfloat yfactor
JNI_GL_BEGIN1
  glPixelZoom(xfactor,yfactor);
JNI_GL_END

JNI_GL_DECLARE1(glPointSize)
  jfloat size
JNI_GL_BEGIN1
  glPointSize(size);
JNI_GL_END

JNI_GL_DECLARE1(glPolygonMode)
  jint face, jint mode
JNI_GL_BEGIN1
  glPolygonMode(face,mode);
JNI_GL_END

JNI_GL_DECLARE1(glPolygonOffset)
  jfloat factor, jfloat units
JNI_GL_BEGIN1
  glPolygonOffset(factor,units);
JNI_GL_END

JNI_GL_DECLARE1(glPolygonStipple)
  jbyteArray jmask
JNI_GL_BEGIN1
  JubyteArray mask(env,jmask);
  glPolygonStipple(mask);
JNI_GL_END

JNI_GL_DECLARE0(glPopAttrib)
JNI_GL_BEGIN0
  glPopAttrib();
JNI_GL_END

JNI_GL_DECLARE0(glPopClientAttrib)
JNI_GL_BEGIN0
  glPopClientAttrib();
JNI_GL_END

JNI_GL_DECLARE0(glPopMatrix)
JNI_GL_BEGIN0
  glPopMatrix();
JNI_GL_END

JNI_GL_DECLARE0(glPopName)
JNI_GL_BEGIN0
  glPopName();
JNI_GL_END

JNI_GL_DECLARE1(glPrioritizeTextures)
  jint n, jintArray jtextures, jfloatArray jpriorities
JNI_GL_BEGIN1
  JuintArray textures(env,jtextures);
  JfloatArray priorities(env,jpriorities);
  glPrioritizeTextures(n,textures,priorities);
JNI_GL_END

JNI_GL_DECLARE1(glPushAttrib)
  jint mask
JNI_GL_BEGIN1
  glPushAttrib(mask);
JNI_GL_END

JNI_GL_DECLARE1(glPushClientAttrib)
  jint mask
JNI_GL_BEGIN1
  glPushClientAttrib(mask);
JNI_GL_END

JNI_GL_DECLARE0(glPushMatrix)
JNI_GL_BEGIN0
  glPushMatrix();
JNI_GL_END

JNI_GL_DECLARE1(glPushName)
  jint name
JNI_GL_BEGIN1
  glPushName(name);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2d)
  jdouble x, jdouble y
JNI_GL_BEGIN1
  glRasterPos2d(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glRasterPos2dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2f)
  jfloat x, jfloat y
JNI_GL_BEGIN1
  glRasterPos2f(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glRasterPos2fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2i)
  jint x, jint y
JNI_GL_BEGIN1
  glRasterPos2i(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glRasterPos2iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2s)
  jshort x, jshort y
JNI_GL_BEGIN1
  glRasterPos2s(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos2sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glRasterPos2sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3d)
  jdouble x, jdouble y, jdouble z
JNI_GL_BEGIN1
  glRasterPos3d(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glRasterPos3dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3f)
  jfloat x, jfloat y, jfloat z
JNI_GL_BEGIN1
  glRasterPos3f(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glRasterPos3fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3i)
  jint x, jint y, jint z
JNI_GL_BEGIN1
  glRasterPos3i(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glRasterPos3iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3s)
  jshort x, jshort y, jshort z
JNI_GL_BEGIN1
  glRasterPos3s(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos3sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glRasterPos3sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4d)
  jdouble x, jdouble y, jdouble z, jdouble w
JNI_GL_BEGIN1
  glRasterPos4d(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glRasterPos4dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4f)
  jfloat x, jfloat y, jfloat z, jfloat w
JNI_GL_BEGIN1
  glRasterPos4f(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glRasterPos4fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4i)
  jint x, jint y, jint z, jint w
JNI_GL_BEGIN1
  glRasterPos4i(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glRasterPos4iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4s)
  jshort x, jshort y, jshort z, jshort w
JNI_GL_BEGIN1
  glRasterPos4s(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glRasterPos4sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glRasterPos4sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glReadBuffer)
  jint mode
JNI_GL_BEGIN1
  glReadBuffer(mode);
JNI_GL_END

JNI_GL_DECLARE1(glReadPixels__IIIIII_3B)
  jint x, jint y, jint width, jint height,
  jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glReadPixels(x,y,width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glReadPixels__IIIIII_3I)
  jint x, jint y, jint width, jint height,
  jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glReadPixels(x,y,width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glReadPixels__IIIIII_3S)
  jint x, jint y, jint width, jint height,
  jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glReadPixels(x,y,width,height,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glRectd)
  jdouble x1, jdouble y1, jdouble x2, jdouble y2
JNI_GL_BEGIN1
  glRectd(x1,y1,x2,y2);
JNI_GL_END

JNI_GL_DECLARE1(glRectdv)
  jdoubleArray jv1, jdoubleArray jv2
JNI_GL_BEGIN1
  JdoubleArray v1(env,jv1);
  JdoubleArray v2(env,jv2);
  glRectdv(v1,v2);
JNI_GL_END

JNI_GL_DECLARE1(glRectf)
  jfloat x1, jfloat y1, jfloat x2, jfloat y2
JNI_GL_BEGIN1
  glRectf(x1,y1,x2,y2);
JNI_GL_END

JNI_GL_DECLARE1(glRectfv)
  jfloatArray jv1, jfloatArray jv2
JNI_GL_BEGIN1
  JfloatArray v1(env,jv1);
  JfloatArray v2(env,jv2);
  glRectfv(v1,v2);
JNI_GL_END

JNI_GL_DECLARE1(glRecti)
  jint x1, jint y1, jint x2, jint y2
JNI_GL_BEGIN1
  glRecti(x1,y1,x2,y2);
JNI_GL_END

JNI_GL_DECLARE1(glRectiv)
  jintArray jv1, jintArray jv2
JNI_GL_BEGIN1
  JintArray v1(env,jv1);
  JintArray v2(env,jv2);
  glRectiv(v1,v2);
JNI_GL_END

JNI_GL_DECLARE1(glRects)
  jshort x1, jshort y1, jshort x2, jshort y2
JNI_GL_BEGIN1
  glRects(x1,y1,x2,y2);
JNI_GL_END

JNI_GL_DECLARE1(glRectsv)
  jshortArray jv1, jshortArray jv2
JNI_GL_BEGIN1
  JshortArray v1(env,jv1);
  JshortArray v2(env,jv2);
  glRectsv(v1,v2);
JNI_GL_END

JNI_GL_DECLARE_RETURN1(jint,glRenderMode)
  jint mode
JNI_GL_BEGIN1
  return glRenderMode(mode);
JNI_GL_END

JNI_GL_DECLARE1(glRotated)
  jdouble angle, jdouble x, jdouble y, jdouble z
JNI_GL_BEGIN1
  glRotated(angle,x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glRotatef)
  jfloat angle, jfloat x, jfloat y, jfloat z
JNI_GL_BEGIN1
  glRotatef(angle,x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glScaled)
  jdouble x, jdouble y, jdouble z
JNI_GL_BEGIN1
  glScaled(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glScalef)
  jfloat x, jfloat y, jfloat z
JNI_GL_BEGIN1
  glScalef(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glScissor)
  jint x, jint y, jint width, jint height
JNI_GL_BEGIN1
  glScissor(x,y,width,height);
JNI_GL_END

JNI_GL_DECLARE1(glSelectBuffer)
  jint size, jobject jbuffer
JNI_GL_BEGIN1
  JuintBuffer buffer(env,jbuffer);
  glSelectBuffer(size,buffer);
JNI_GL_END

JNI_GL_DECLARE1(glShadeModel)
  jint mode
JNI_GL_BEGIN1
  glShadeModel(mode);
JNI_GL_END

JNI_GL_DECLARE1(glStencilFunc)
  jint func, jint ref, jint mask
JNI_GL_BEGIN1
  glStencilFunc(func,ref,mask);
JNI_GL_END

JNI_GL_DECLARE1(glStencilMask)
  jint mask
JNI_GL_BEGIN1
  glStencilMask(mask);
JNI_GL_END

JNI_GL_DECLARE1(glStencilOp)
  jint fail, jint zfail, jint zpass
JNI_GL_BEGIN1
  glStencilOp(fail,zfail,zpass);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1d)
  jdouble s
JNI_GL_BEGIN1
  glTexCoord1d(s);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glTexCoord1dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1f)
  jfloat s
JNI_GL_BEGIN1
  glTexCoord1f(s);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glTexCoord1fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1i)
  jint s
JNI_GL_BEGIN1
  glTexCoord1i(s);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glTexCoord1iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1s)
  jshort s
JNI_GL_BEGIN1
  glTexCoord1s(s);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord1sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glTexCoord1sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2d)
  jdouble s, jdouble t
JNI_GL_BEGIN1
  glTexCoord2d(s,t);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glTexCoord2dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2f)
  jfloat s, jfloat t
JNI_GL_BEGIN1
  glTexCoord2f(s,t);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glTexCoord2fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2i)
  jint s, jint t
JNI_GL_BEGIN1
  glTexCoord2i(s,t);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glTexCoord2iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2s)
  jshort s, jshort t
JNI_GL_BEGIN1
  glTexCoord2s(s,t);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord2sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glTexCoord2sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3d)
  jdouble s, jdouble t, jdouble r
JNI_GL_BEGIN1
  glTexCoord3d(s,t,r);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glTexCoord3dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3f)
  jfloat s, jfloat t, jfloat r
JNI_GL_BEGIN1
  glTexCoord3f(s,t,r);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glTexCoord3fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3i)
  jint s, jint t, jint r
JNI_GL_BEGIN1
  glTexCoord3i(s,t,r);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glTexCoord3iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3s)
  jshort s, jshort t, jshort r
JNI_GL_BEGIN1
  glTexCoord3s(s,t,r);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord3sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glTexCoord3sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4d)
  jdouble s, jdouble t, jdouble r, jdouble q
JNI_GL_BEGIN1
  glTexCoord4d(s,t,r,q);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glTexCoord4dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4f)
  jfloat s, jfloat t, jfloat r, jfloat q
JNI_GL_BEGIN1
  glTexCoord4f(s,t,r,q);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glTexCoord4fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4i)
  jint s, jint t, jint r, jint q
JNI_GL_BEGIN1
  glTexCoord4i(s,t,r,q);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glTexCoord4iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4s)
  jshort s, jshort t, jshort r, jshort q
JNI_GL_BEGIN1
  glTexCoord4s(s,t,r,q);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoord4sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glTexCoord4sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glTexCoordPointer)
  jint size, jint type, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glTexCoordPointer(size,type,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glTexEnvf)
  jint target, jint pname, jfloat param
JNI_GL_BEGIN1
  glTexEnvf(target,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexEnvfv)
  jint target, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glTexEnvfv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexEnvi)
  jint target, jint pname, jint param
JNI_GL_BEGIN1
  glTexEnvi(target,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexEnviv)
  jint target, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glTexEnviv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexGend)
  jint coord, jint pname, jdouble param
JNI_GL_BEGIN1
  glTexGend(coord,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexGendv)
  jint coord, jint pname, jdoubleArray jparams
JNI_GL_BEGIN1
  JdoubleArray params(env,jparams);
  glTexGendv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexGenf)
  jint coord, jint pname, jfloat param
JNI_GL_BEGIN1
  glTexGenf(coord,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexGenfv)
  jint coord, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glTexGenfv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexGeni)
  jint coord, jint pname, jint param
JNI_GL_BEGIN1
  glTexGeni(coord,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexGeniv)
  jint coord, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glTexGeniv(coord,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage1D__IIIIIII_3B)
  jint target, jint level, jint internalformat,
  jint width, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage1D(target,level,internalformat,width,border,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage1D__IIIIIII_3I)
  jint target, jint level, jint internalformat,
  jint width, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage1D(target,level,internalformat,width,border,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage1D__IIIIIII_3S)
  jint target, jint level, jint internalformat,
  jint width, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage1D(target,level,internalformat,width,border,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage2D__IIIIIIII_3B)
  jint target, jint level, jint internalformat,
  jint width, jint height, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage2D(
    target,level,internalformat,width,height,border,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage2D__IIIIIIII_3I)
  jint target, jint level, jint internalformat,
  jint width, jint height, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage2D(
    target,level,internalformat,width,height,border,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexImage2D__IIIIIIII_3S)
  jint target, jint level, jint internalformat,
  jint width, jint height, jint border, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexImage2D(
    target,level,internalformat,width,height,border,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexParameterf)
  jint target, jint pname, jfloat param
JNI_GL_BEGIN1
  glTexParameterf(target,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexParameterfv)
  jint target, jint pname, jfloatArray jparams
JNI_GL_BEGIN1
  JfloatArray params(env,jparams);
  glTexParameterfv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexParameteri)
  jint target, jint pname, jint param
JNI_GL_BEGIN1
  glTexParameteri(target,pname,param);
JNI_GL_END

JNI_GL_DECLARE1(glTexParameteriv)
  jint target, jint pname, jintArray jparams
JNI_GL_BEGIN1
  JintArray params(env,jparams);
  glTexParameteriv(target,pname,params);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage1D__IIIIII_3B)
  jint target, jint level, jint xoffset,
  jint width, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage1D(target,level,xoffset,width,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage1D__IIIIII_3I)
  jint target, jint level, jint xoffset,
  jint width, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage1D(target,level,xoffset,width,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage1D__IIIIII_3S)
  jint target, jint level, jint xoffset,
  jint width, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage1D(target,level,xoffset,width,format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage2D__IIIIIIII_3B)
  jint target, jint level, jint xoffset, jint yoffset,
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage2D(
    target,level,xoffset,yoffset,width,height,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage2D__IIIIIIII_3I)
  jint target, jint level, jint xoffset, jint yoffset,
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage2D(
    target,level,xoffset,yoffset,width,height,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTexSubImage2D__IIIIIIII_3S)
  jint target, jint level, jint xoffset, jint yoffset,
  jint width, jint height, jint format, jint type, jarray jpixels
JNI_GL_BEGIN1
  JvoidArray pixels(env,jpixels);
  glTexSubImage2D(
    target,level,xoffset,yoffset,width,height,
    format,type,pixels);
JNI_GL_END

JNI_GL_DECLARE1(glTranslated)
  jdouble x, jdouble y, jdouble z
JNI_GL_BEGIN1
  glTranslated(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glTranslatef)
  jfloat x, jfloat y, jfloat z
JNI_GL_BEGIN1
  glTranslatef(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2d)
  jdouble x, jdouble y
JNI_GL_BEGIN1
  glVertex2d(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glVertex2dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2f)
  jfloat x, jfloat y
JNI_GL_BEGIN1
  glVertex2f(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glVertex2fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2i)
  jint x, jint y
JNI_GL_BEGIN1
  glVertex2i(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glVertex2iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2s)
  jshort x, jshort y
JNI_GL_BEGIN1
  glVertex2s(x,y);
JNI_GL_END

JNI_GL_DECLARE1(glVertex2sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glVertex2sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3d)
  jdouble x, jdouble y, jdouble z
JNI_GL_BEGIN1
  glVertex3d(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glVertex3dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3f)
  jfloat x, jfloat y, jfloat z
JNI_GL_BEGIN1
  glVertex3f(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glVertex3fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3i)
  jint x, jint y, jint z
JNI_GL_BEGIN1
  glVertex3i(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glVertex3iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3s)
  jshort x, jshort y, jshort z
JNI_GL_BEGIN1
  glVertex3s(x,y,z);
JNI_GL_END

JNI_GL_DECLARE1(glVertex3sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glVertex3sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4d)
  jdouble x, jdouble y, jdouble z, jdouble w
JNI_GL_BEGIN1
  glVertex4d(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4dv)
  jdoubleArray jv
JNI_GL_BEGIN1
  JdoubleArray v(env,jv);
  glVertex4dv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4f)
  jfloat x, jfloat y, jfloat z, jfloat w
JNI_GL_BEGIN1
  glVertex4f(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4fv)
  jfloatArray jv
JNI_GL_BEGIN1
  JfloatArray v(env,jv);
  glVertex4fv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4i)
  jint x, jint y, jint z, jint w
JNI_GL_BEGIN1
  glVertex4i(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4iv)
  jintArray jv
JNI_GL_BEGIN1
  JintArray v(env,jv);
  glVertex4iv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4s)
  jshort x, jshort y, jshort z, jshort w
JNI_GL_BEGIN1
  glVertex4s(x,y,z,w);
JNI_GL_END

JNI_GL_DECLARE1(glVertex4sv)
  jshortArray jv
JNI_GL_BEGIN1
  JshortArray v(env,jv);
  glVertex4sv(v);
JNI_GL_END

JNI_GL_DECLARE1(glVertexPointer)
  jint size, jint type, jint stride, jobject jpointer
JNI_GL_BEGIN1
  JvoidBuffer pointer(env,jpointer);
  glVertexPointer(size,type,stride,pointer);
JNI_GL_END

JNI_GL_DECLARE1(glViewport)
  jint x, jint y, jint width, jint height
JNI_GL_BEGIN1
  glViewport(x,y,width,height);
JNI_GL_END

/////////////////////////////////////////////////////////////////////////////
// OpenGL 1.2

JNI_GL_DECLARE2(glBlendColor)
  jfloat red, jfloat green, jfloat blue, jfloat alpha
JNI_GL_BEGIN2
  (*(PFNGLBLENDCOLORPROC)toPointer(pfunc))
    (red,green,blue,alpha);
JNI_GL_END

JNI_GL_DECLARE2(glBlendEquation)
  jint mode
JNI_GL_BEGIN2
  (*(PFNGLBLENDEQUATIONPROC)toPointer(pfunc))
    (mode);
JNI_GL_END

JNI_GL_DECLARE2(glDrawRangeElements__IIIII_3B)
  jint mode, jint start, jint end, jint count, jint type, jarray jindices
JNI_GL_BEGIN2
  JvoidArray indices(env,jindices);
  (*(PFNGLDRAWRANGEELEMENTSPROC)toPointer(pfunc))
    (mode,start,end,count,type,indices);
JNI_GL_END

JNI_GL_DECLARE2(glDrawRangeElements__IIIII_3I)
  jint mode, jint start, jint end, jint count, jint type, jarray jindices
JNI_GL_BEGIN2
  JvoidArray indices(env,jindices);
  (*(PFNGLDRAWRANGEELEMENTSPROC)toPointer(pfunc))
    (mode,start,end,count,type,indices);
JNI_GL_END

JNI_GL_DECLARE2(glDrawRangeElements__IIIII_3S)
  jint mode, jint start, jint end, jint count, jint type, jarray jindices
JNI_GL_BEGIN2
  JvoidArray indices(env,jindices);
  (*(PFNGLDRAWRANGEELEMENTSPROC)toPointer(pfunc))
    (mode,start,end,count,type,indices);
JNI_GL_END

/*
  private static native void nglDrawRangeElements(long pfunc,
    int mode, int start, int end, int count, int type, byte[] indices);
  private static native void nglDrawRangeElements(long pfunc,
    int mode, int start, int end, int count, int type, int[] indices);
  private static native void nglDrawRangeElements(long pfunc,
    int mode, int start, int end, int count, int type, short[] indices);
  private static native void nglColorTable(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, byte[] table);
  private static native void nglColorTable(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, int[] table);
  private static native void nglColorTable(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, short[] table);
  private static native void nglColorTableParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglColorTableParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglCopyColorTable(long pfunc,
    int target, int internalformat, int x, int y, int width);
  private static native void nglGetColorTable(long pfunc,
    int target, int format, int type, byte[] table);
  private static native void nglGetColorTable(long pfunc,
    int target, int format, int type, int[] table);
  private static native void nglGetColorTable(long pfunc,
    int target, int format, int type, short[] table);
  private static native void nglGetColorTableParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglGetColorTableParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglColorSubTable(long pfunc,
    int target, int start, int count, int format, int type, byte[] data);
  private static native void nglColorSubTable(long pfunc,
    int target, int start, int count, int format, int type, int[] data);
  private static native void nglColorSubTable(long pfunc,
    int target, int start, int count, int format, int type, short[] data);
  private static native void nglCopyColorSubTable(long pfunc,
    int target, int start, int x, int y, int width);
  private static native void nglConvolutionFilter1D(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, byte[] image);
  private static native void nglConvolutionFilter1D(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, float[] image);
  private static native void nglConvolutionFilter1D(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, int[] image);
  private static native void nglConvolutionFilter1D(long pfunc,
    int target, int internalformat, int width, 
    int format, int type, short[] image);
  private static native void nglConvolutionFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, byte[] image);
  private static native void nglConvolutionFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, float[] image);
  private static native void nglConvolutionFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, int[] image);
  private static native void nglConvolutionFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, short[] image);
  private static native void nglConvolutionParameterf(long pfunc,
    int target, int pname, float param);
  private static native void nglConvolutionParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglConvolutionParameteri(long pfunc,
    int target, int pname, int param);
  private static native void nglConvolutionParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglCopyConvolutionFilter1D(long pfunc,
    int target, int internalformat, int x, int y, int width);
  private static native void nglCopyConvolutionFilter2D(long pfunc,
    int target, int internalformat, int x, int y, int width, int height);
  private static native void nglGetConvolutionFilter(long pfunc,
    int target, int format, int type, byte[] image);
  private static native void nglGetConvolutionFilter(long pfunc,
    int target, int format, int type, float[] image);
  private static native void nglGetConvolutionFilter(long pfunc,
    int target, int format, int type, int[] image);
  private static native void nglGetConvolutionFilter(long pfunc,
    int target, int format, int type, short[] image);
  private static native void nglGetConvolutionParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglGetConvolutionParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglGetSeparableFilter(long pfunc,
    int target, int format, int type, 
    byte[] row, byte[] column, byte[] span);
  private static native void nglGetSeparableFilter(long pfunc,
    int target, int format, int type, 
    float[] row, float[] column, float[] span);
  private static native void nglGetSeparableFilter(long pfunc,
    int target, int format, int type, 
    int[] row, int[] column, int[] span);
  private static native void nglGetSeparableFilter(long pfunc,
    int target, int format, int type, 
    short[] row, short[] column, short[] span);
  private static native void nglSeparableFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, byte[] row, byte[] column);
  private static native void nglSeparableFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, float[] row, float[] column);
  private static native void nglSeparableFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, int[] row, int[] column);
  private static native void nglSeparableFilter2D(long pfunc,
    int target, int internalformat, int width, int height, 
    int format, int type, short[] row, short[] column);
  private static native void nglGetHistogram(long pfunc,
    int target, boolean reset, int format, int type, byte[] values);
  private static native void nglGetHistogram(long pfunc,
    int target, boolean reset, int format, int type, float[] values);
  private static native void nglGetHistogram(long pfunc,
    int target, boolean reset, int format, int type, int[] values);
  private static native void nglGetHistogram(long pfunc,
    int target, boolean reset, int format, int type, short[] values);
  private static native void nglGetHistogramParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglGetHistogramParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglGetMinmax(long pfunc,
    int target, boolean reset, int format, int type, byte[] values);
  private static native void nglGetMinmax(long pfunc,
    int target, boolean reset, int format, int type, float[] values);
  private static native void nglGetMinmax(long pfunc,
    int target, boolean reset, int format, int type, int[] values);
  private static native void nglGetMinmax(long pfunc,
    int target, boolean reset, int format, int type, short[] values);
  private static native void nglGetMinmaxParameterfv(long pfunc,
    int target, int pname, float[] params);
  private static native void nglGetMinmaxParameteriv(long pfunc,
    int target, int pname, int[] params);
  private static native void nglHistogram(long pfunc,
    int target, int width, int internalformat, boolean sink);
  private static native void nglMinmax(long pfunc,
    int target, int internalformat, boolean sink);
  private static native void nglResetHistogram(long pfunc,
    int target);
  private static native void nglResetMinmax(long pfunc,
    int target);
  private static native void nglTexImage3D(long pfunc,
    int target, int level, int internalformat, int width, int height, 
    int depth, int border, int format, int type, byte[] pixels);
  private static native void nglTexImage3D(long pfunc,
    int target, int level, int internalformat, int width, int height, 
    int depth, int border, int format, int type, int[] pixels);
  private static native void nglTexImage3D(long pfunc,
    int target, int level, int internalformat, int width, int height, 
    int depth, int border, int format, int type, short[] pixels);
  private static native void nglTexSubImage3D(long pfunc,
    int target, int level, int xoffset, int yoffset, int zoffset, 
    int width, int height, int depth, int format, int type, 
    byte[] pixels);
  private static native void nglTexSubImage3D(long pfunc,
    int target, int level, int xoffset, int yoffset, int zoffset, 
    int width, int height, int depth, int format, int type, 
    int[] pixels);
  private static native void nglTexSubImage3D(long pfunc,
    int target, int level, int xoffset, int yoffset, int zoffset, 
    int width, int height, int depth, int format, int type, 
    short[] pixels);
  private static native void nglCopyTexSubImage3D(long pfunc,
    int target, int level, int xoffset, int yoffset, int zoffset, 
    int x, int y, int width, int height);
*/
