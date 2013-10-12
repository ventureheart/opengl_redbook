#include<GL/glut.h>

#define checkImageWidth 64
#define checkImageHeight 64
#define histogram_size 256

static GLubyte checkImage[checkImageHeight][checkImageWidth][3];

void makeCheckImage(void) {
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = (((i&0x8) == 0) ^ ((j&0x8) == 0)) * 255;
            checkImage[i][j][0] = (GLubyte)c;
            checkImage[i][j][1] = (GLubyte)0;
            checkImage[i][j][2] = (GLubyte)c;
        }
    }
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glHistogram(GL_HISTOGRAM, histogram_size, GL_RGB, GL_FALSE);
    glEnable(GL_HISTOGRAM);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, GL_UNSIGNED_BYTE, checkImage);

    int i;
    GLushort values[histogram_size][3];
    glGetHistogram(GL_HISTOGRAM, GL_TRUE, GL_RGB, GL_UNSIGNED_SHORT, values);

    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        for (i = 0; i < histogram_size; i++)
            glVertex2s(i, values[i][0]);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 0.0);
        for (i = 0; i < histogram_size; i++)
            glVertex2s(i, values[i][1]);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.0, 1.0);
        for (i = 0; i < histogram_size; i++)
            glVertex2s(i, values[i][2]);
    glEnd();

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: image");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
