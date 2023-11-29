package com.guangoon.learnopengl;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeInit();

    public native void nativeDrawFrame();

    public native void nativeSurfaceChanged(int width, int height);

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        nativeInit();
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        nativeDrawFrame();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        nativeSurfaceChanged(width, height);
    }
}
