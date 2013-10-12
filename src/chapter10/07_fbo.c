#include<GL/glut.h>
#include<stdio.h>

enum {Color, Depth, NumRenderbuffers};
GLuint framebuffer, renderbuffer[NumRenderbuffers];

void init() {
    glGenRenderbuffers(NumRenderbuffers, renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer[Color]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 256, 256);
    
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer[Depth]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 256, 256);
    
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, renderbuffer[Color]);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, renderbuffer[Depth]);

    glEnable(GL_DEPTH_TEST);
}

void display() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, 256, 256);

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    /* attached fbo to drawing buffer, then you can render to fbo instead of window Framebuffer */
    //

    /* attach fbo to read buffer and detach fbo to draw buffer, then you can read from fbo 
       and draw to window FrameBuffer to show it */
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBlitFramebuffer(0, 0, 255, 255, 0, 0, 255, 255, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_ACCUM | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Frustrum");
    
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
