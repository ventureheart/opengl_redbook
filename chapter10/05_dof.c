#include<GL/glut.h>
#include<stdio.h>

GLuint teapotList;

void init() {
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};
    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearAccum(0.0, 0.0, 0.0, 0.0);

    teapotList = glGenLists(1);
    glNewList(teapotList, GL_COMPILE);
    glutSolidTeapot(0.5);
    glEndList();
}

void renderTeapot(GLfloat x, GLfloat y, GLfloat z,
                  GLfloat ambr, GLfloat ambg, GLfloat ambb,
                  GLfloat difr, GLfloat difg, GLfloat difb,
                  GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
    GLfloat mat[4];
    
    glPushMatrix();
    glTranslatef(x, y, z);

    mat[0] = ambr, mat[1] = ambg, mat[2] = ambb, mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);

    mat[0] = difr, mat[1] = difg, mat[2] = difb;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);

    mat[0] = specr, mat[1] = specg, mat[2] = specb;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    
    glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);

    glCallList(teapotList);
    glPopMatrix();
}

void display() {
    int jitter;
    
    struct Test{
        int x;
        int y;
    };
    
    struct Test j8[8] = {0};
    
    GLint viewport[4];
   
    glGetIntegerv(GL_VIEWPORT, viewport);
    glClear(GL_ACCUM_BUFFER_BIT);
    
    for(jitter = 0; jitter < 8; jitter++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        accPerspective(45.0, (GLdouble)viewport[2]/(GLdouble)viewport[3], 1.0,
        //gluLookAt(45.0, (GLdouble)viewport[2]/(GLdouble)viewport[3], 1.0,
                       15.0, 0.0, 0.0, 
                       0.33 * j8[jitter].x, 0.33 * j8[jitter].y, 5.0);
        
        renderTeapot(-1.1, -0.5, -4.5,
                     0.1745, 0.01175, 0.01175,
                     0.61424, 0.04136, 0.04136, 
                     0.727811, 0.626959, 0.626959, 0.6);
        
        renderTeapot(-0.5, -0.5, -5.0,
                     0.24725, 0.1995, 0.0745,
                     0.75164, 0.60648, 0.22648, 
                     0.628281, 0.555802, 0.366065, 0.4);
        
        renderTeapot(0.2, -0.5, -5.5,
                     0.19225, 0.19225, 0.19225,
                     0.50754, 0.50754, 0.50754, 
                     0.508273, 0.508273, 0.508273, 0.4);
        
        renderTeapot(1.0, -0.5, -6.0,
                     0.0215, 0.1745, 0.0215,
                     0.07568, 0.61424, 0.07568, 
                     0.633, 0.727811, 0.633, 0.6);
        
        renderTeapot(1.8, -0.5, -6.5,
                     0.0, 0.1, 0.06,
                     0.0, 0.50980392, 0.50980392, 
                     0.50196078, 0.50196078, 0.50196078, 0.25);
        glAccum(GL_ACCUM, 0.125);
    }
    glAccum(GL_RETURN, 1.0);
    glFlush();
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
