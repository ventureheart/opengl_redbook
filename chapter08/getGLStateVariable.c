#include<GL/glut.h>
#include<stdio.h>

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutCreateWindow("getGLStateVariable");
    float color[4] = {1.0, 0.0, 0.0, 1.0};
    glGetFloatv(GL_CURRENT_RASTER_COLOR, color);
    printf("current color: %f, %f, %f, %f.\n", color[0], color[1], color[2], color[3]);
}
