#include <GL/glut.h>
#include <stdio.h>

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

#define checkImageWidth 64
#define checkImageHeight 64

static GLubyte checkImage[checkImageHeight][checkImageWidth][3];
static GLint height;

static GLuint pixelBuffer;
static GLsizei imageWidth = 64;
static GLsizei imageHeight = 64;
static GLsizei numComponents = 4;
static GLsizei bufferSize;

void makeCheckImage(void) {
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++) {
        for (j = 0; j < checkImageWidth; j++) {
            c = (((i&0x8) == 0) ^ ((j&0x8) == 0)) * 255;
            checkImage[i][j][0] = (GLubyte)c;
            checkImage[i][j][1] = (GLubyte)c;
            checkImage[i][j][2] = (GLubyte)c;
        }
    }
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    bufferSize = imageWidth * imageHeight * numComponents * sizeof(GLfloat);
    glGenBuffers(1, &pixelBuffer);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pixelBuffer);
    glBufferData(GL_PIXEL_PACK_BUFFER, bufferSize, NULL, GL_STREAM_READ);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, GL_UNSIGNED_BYTE, checkImage);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    height = (GLint)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void motion(int x, int y) {
    static GLint screeny;
    GLsizei numPixels = imageWidth * imageHeight;

    screeny = height - (GLint)y;
    //glRasterPos2i(x, screeny);
    glReadPixels(0, 0, imageWidth, imageHeight, GL_RGBA, GL_FLOAT, BUFFER_OFFSET(0));
    GLfloat *pixels = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

    int i;
    for (i = 0; i < numPixels; i++) {
        printf("%f ", pixels[0]);
    }
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    //glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: image");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMainLoop();
}
