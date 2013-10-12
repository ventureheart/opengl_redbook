#include<GL/glut.h>
#include<stdio.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ACCUM | GLUT_DEPTH | GLUT_STENCIL);
    glutCreateWindow("get frame buffer bits");
    
    //int color[4] = {0};
    int color[3] = {0};
    int alpha = 0;
    glGetIntegerv(GL_RED_BITS, color);
    glGetIntegerv(GL_GREEN_BITS, &color[1]);
    glGetIntegerv(GL_BLUE_BITS, &color[2]);
    //glGetIntegerv(GL_ALPHA_BITS, &color[3]);
    glGetIntegerv(GL_ALPHA_BITS, &alpha);
    printf("Color Framebuffer bits: R:%d, G:%d, B:%d, Alpha:%d.\n", color[0], color[1], color[2], alpha);
    
    int index = 0, depth = 0, stencil = 0;
    int accumColor[4] = {4};
    glGetIntegerv(GL_INDEX_BITS, &index);
    glGetIntegerv(GL_DEPTH_BITS, &depth);
    glGetIntegerv(GL_STENCIL_BITS, &stencil);
    glGetIntegerv(GL_ACCUM_RED_BITS, accumColor);
    printf("Index Framebuffer bits: %d\n", index);
    printf("Depth Framebuffer bits: %d\n", depth);
    printf("Stencil Framebuffer bits: %d\n", stencil);
    printf("Accumulate Framebuffer bits: R:%d\n", accumColor[0]);
    
    GLboolean stereo = false;
    GLboolean doubleBuffer = false;
    glGetBooleanv(GL_STEREO, &stereo);
    glGetBooleanv(GL_DOUBLEBUFFER, &doubleBuffer);
    stereo == true ? printf("stereo: Yes \n") : printf("stereo: No \n");
    doubleBuffer == true ? printf("double buffer: Yes \n") : printf("double buffer: No \n");
    
    int auxBufferNum = 0;
    glGetIntegerv(GL_AUX_BUFFERS, &auxBufferNum);
    printf("Auxilary buffer number: %d\n", auxBufferNum);
    return 1;
}
