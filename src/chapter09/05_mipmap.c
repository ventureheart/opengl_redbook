#include<GL/glut.h>
#include<stdio.h>

static GLubyte mipmapImage32[32][32][4];
static GLubyte mipmapImage16[16][16][4];
static GLubyte mipmapImage8[8][8][4];
static GLubyte mipmapImage4[4][4][4];
static GLubyte mipmapImage2[2][2][4];
static GLubyte mipmapImage1[1][1][4];
static GLuint texName;

void makeImage(void) {
    int i, j;

    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32; j++) {
            mipmapImage32[i][j][0] = (GLubyte)255;
            mipmapImage32[i][j][1] = (GLubyte)255;
            mipmapImage32[i][j][2] = (GLubyte)0;
            mipmapImage32[i][j][3] = (GLubyte)255;
        }
    }

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            mipmapImage16[i][j][0] = (GLubyte)255;
            mipmapImage16[i][j][1] = (GLubyte)0;
            mipmapImage16[i][j][2] = (GLubyte)255;
            mipmapImage16[i][j][3] = (GLubyte)255;
        }
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            mipmapImage8[i][j][0] = (GLubyte)255;
            mipmapImage8[i][j][1] = (GLubyte)0;
            mipmapImage8[i][j][2] = (GLubyte)0;
            mipmapImage8[i][j][3] = (GLubyte)255;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            mipmapImage4[i][j][0] = (GLubyte)0;
            mipmapImage4[i][j][1] = (GLubyte)255;
            mipmapImage4[i][j][2] = (GLubyte)0;
            mipmapImage4[i][j][3] = (GLubyte)255;
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            mipmapImage2[i][j][0] = (GLubyte)0;
            mipmapImage2[i][j][1] = (GLubyte)0;
            mipmapImage2[i][j][2] = (GLubyte)255;
            mipmapImage2[i][j][3] = (GLubyte)255;
        }
    }

    mipmapImage1[0][0][0] = (GLubyte)255;
    mipmapImage1[0][0][1] = (GLubyte)255;
    mipmapImage1[0][0][2] = (GLubyte)255;
    mipmapImage1[0][0][3] = (GLubyte)255;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(0.0, 0.0, -3.6);
    makeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage32);
    glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage16);
    glTexImage2D(GL_TEXTURE_2D, 2, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage8);
    glTexImage2D(GL_TEXTURE_2D, 3, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage4);
    glTexImage2D(GL_TEXTURE_2D, 4, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage2);
    glTexImage2D(GL_TEXTURE_2D, 5, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, mipmapImage1);
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) {
        printf("create texture succeed.\n");
    } else {
        printf("create texture failed, error code = %x.\n", error);
    }
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
        glTexCoord2f(0.0, 8.0); glVertex3f(-2.0, 1.0, 0.0);
        glTexCoord2f(8.0, 8.0); glVertex3f(2000.0, 1.0, -6000.0);
        glTexCoord2f(8.0, 0.0); glVertex3f(2000.0, -1.0, -6000.0);
    glEnd();
    glFlush();
    //glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: checker.");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
