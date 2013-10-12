#include<GL/glut.h>

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void lineSegment(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(10);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
/*    glBegin(GL_LINES);
        //glVertex2i(180, 15);
        //glVertex2i(10, 145);
    glEnd();
*/
    //glBegin(GL_LINE_LOOP);
    glBegin(GL_TRIANGLES);
        glVertex2i(200, 200);
        glVertex2i(200, 100);
        glVertex2i(300, 100);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(50, 200);
        glVertex2i(150, 100);
    glEnd();

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A sample opengl app.");

    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}
