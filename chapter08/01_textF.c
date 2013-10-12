#include<GL/glut.h>

GLubyte rasters[24] = {
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xff, 0x00,
    0xff, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xff, 0xc0,
    0xff, 0xc0
};

void init(void) {
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    //glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawTextF(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glWindowPos2i(20, 20);
    //glRasterPos2i(20, 20);				//glRasterPos* function has been depreacted in openGL 3.0? so the current raster location is invalid, then glBitmap will draw nothing. 
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: drawTextF");

    init();
    glutDisplayFunc(drawTextF);
    glutMainLoop();
}
