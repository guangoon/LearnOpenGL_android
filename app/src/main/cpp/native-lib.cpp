#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <string>


extern "C" {
    JNIEXPORT void JNICALL
    Java_com_guangoon_learnopengl_GLRenderer_nativeInit(JNIEnv* env, jobject obj);

    JNIEXPORT void JNICALL
    Java_com_guangoon_learnopengl_GLRenderer_nativeDrawFrame(JNIEnv* env, jobject obj);

    JNIEXPORT void JNICALL
    Java_com_guangoon_learnopengl_GLRenderer_nativeSurfaceChanged(JNIEnv* env, jobject obj, jint width, jint height);
}

GLuint program;
GLuint positionHandle;

const char* vertexShaderCode =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

const char* fragmentShaderCode =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        __android_log_print(ANDROID_LOG_ERROR, "GLRenderer", "after %s() glError (0x%x)\n", op, error);
    }
}

void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    positionHandle = glGetAttribLocation(program, "vPosition");

    checkGlError("initShaders");
}

void renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    GLfloat vertices[] = {
        0.0f,  0.5f,
       -0.5f, -0.5f,
        0.5f, -0.5f
    };

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(positionHandle);

    checkGlError("renderFrame");
}

JNIEXPORT void JNICALL Java_com_guangoon_learnopengl_GLRenderer_nativeInit(JNIEnv* env, jobject obj) {
    initShaders();
}

JNIEXPORT void JNICALL Java_com_guangoon_learnopengl_GLRenderer_nativeDrawFrame(JNIEnv* env, jobject obj) {
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_guangoon_learnopengl_GLRenderer_nativeSurfaceChanged(JNIEnv* env, jobject obj, jint width, jint height) {
    glViewport(0, 0, width, height);
}


