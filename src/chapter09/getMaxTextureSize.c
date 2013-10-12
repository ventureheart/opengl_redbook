#include<GL/glut.h>
#include<stdio.h>

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutCreateWindow("getGLStateVariable");
    int maxSize[4] = {0};
    int major, minor;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxSize);
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("max texture size: %d, %d, %d, %d.\n", maxSize[0], maxSize[1], maxSize[2], maxSize[3]);
    printf("GL Version: %d.%d\n", major, minor);
}
