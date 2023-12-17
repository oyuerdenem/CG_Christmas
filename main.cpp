#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define GL_PI 3.1415f

//GLfloat sunRadius = 1.0f;
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float scale = 1.0f;

GLuint ObjectList;

void init(void)
{
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
/*  be efficient--make teapot display list  */
   /*ObjectList = glGenLists(1);
   glNewList (ObjectList, GL_COMPILE);
   glutSolidTeapot(1.0);
   glEndList ();*/
}

void renderTeapot(GLfloat x, GLfloat y,
   GLfloat ambr, GLfloat ambg, GLfloat ambb,
   GLfloat difr, GLfloat difg, GLfloat difb,
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine)
{
   GLfloat mat[4];

   glPushMatrix();
   glTranslatef(x, y, 0.0);

   mat[0] = ambr;
   mat[1] = ambg;
   mat[2] = ambb;
   mat[3] = 1.0;
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat);

   mat[0] = difr;
   mat[1] = difg;
   mat[2] = difb;
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);

   mat[0] = specr;
   mat[1] = specg;
   mat[2] = specb;
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

   glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
   //glCallList(teapotList);
   glPopMatrix();
}

/*void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   renderTeapot(2.0, 17.0, 0.0215, 0.1745, 0.0215,
      0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
   renderTeapot(2.0, 14.0, 0.135, 0.2225, 0.1575,
      0.54, 0.89, 0.63, 0.316228, 0.316228, 0.316228, 0.1);
   renderTeapot(2.0, 11.0, 0.05375, 0.05, 0.06625,
      0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3);
   renderTeapot(2.0, 8.0, 0.25, 0.20725, 0.20725,
      1, 0.829, 0.829, 0.296648, 0.296648, 0.296648, 0.088);
   renderTeapot(2.0, 5.0, 0.1745, 0.01175, 0.01175,
      0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6);
   renderTeapot(2.0, 2.0, 0.1, 0.18725, 0.1745,
      0.396, 0.74151, 0.69102, 0.297254, 0.30829, 0.306678, 0.1);
   renderTeapot(6.0, 17.0, 0.329412, 0.223529, 0.027451,
      0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843,
      0.21794872);
   renderTeapot(6.0, 14.0, 0.2125, 0.1275, 0.054,
      0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2);
   renderTeapot(6.0, 11.0, 0.25, 0.25, 0.25,
      0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6);
   renderTeapot(6.0, 8.0, 0.19125, 0.0735, 0.0225,
      0.7038, 0.27048, 0.0828, 0.256777, 0.137622, 0.086014, 0.1);
   renderTeapot(6.0, 5.0, 0.24725, 0.1995, 0.0745,
      0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4);
   renderTeapot(6.0, 2.0, 0.19225, 0.19225, 0.19225,
      0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4);
   renderTeapot(10.0, 17.0, 0.0, 0.0, 0.0, 0.01, 0.01, 0.01,
      0.50, 0.50, 0.50, .25);
   renderTeapot(10.0, 14.0, 0.0, 0.1, 0.06, 0.0, 0.50980392, 0.50980392,
      0.50196078, 0.50196078, 0.50196078, .25);
   renderTeapot(10.0, 11.0, 0.0, 0.0, 0.0,
      0.1, 0.35, 0.1, 0.45, 0.55, 0.45, .25);
   renderTeapot(10.0, 8.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0,
      0.7, 0.6, 0.6, .25);
   renderTeapot(10.0, 5.0, 0.0, 0.0, 0.0, 0.55, 0.55, 0.55,
      0.70, 0.70, 0.70, .25);
   renderTeapot(10.0, 2.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.0,
      0.60, 0.60, 0.50, .25);
   renderTeapot(14.0, 17.0, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01,
      0.4, 0.4, 0.4, .078125);
   renderTeapot(14.0, 14.0, 0.0, 0.05, 0.05, 0.4, 0.5, 0.5,
      0.04, 0.7, 0.7, .078125);
   renderTeapot(14.0, 11.0, 0.0, 0.05, 0.0, 0.4, 0.5, 0.4,
      0.04, 0.7, 0.04, .078125);
   renderTeapot(14.0, 8.0, 0.05, 0.0, 0.0, 0.5, 0.4, 0.4,
      0.7, 0.04, 0.04, .078125);
   renderTeapot(14.0, 5.0, 0.05, 0.05, 0.05, 0.5, 0.5, 0.5,
      0.7, 0.7, 0.7, .078125);
   renderTeapot(14.0, 2.0, 0.05, 0.05, 0.0, 0.5, 0.5, 0.4,
      0.7, 0.7, 0.04, .078125);
   glFlush();
}*/

void initLighting() {
    glEnable(GL_LIGHTING);

    GLfloat light_direction[] = {1.0, 1.0, 1.0, 0.0};

    GLfloat light_ambient[] = {1.0, 1.0, 0.0, 1.0}; // Yellow ambient light
    GLfloat light_diffuse[] = {1.0, 1.0, 0.0, 1.0}; // Yellow diffuse light
    GLfloat light_specular[] = {1.0, 1.0, 0.0, 1.0}; // Yellow specular light

    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHT0);
}

void RenderStar(void) {
    float rad_big = 30.0f;
    float rad_small = 15.0f;

    //ОДНЫ БҮХ ӨНЦГИЙН РАДИУСЫГ ХАДГАЛНА.
    float angles[10];
    for(int i=0; i<10; i++){
        angles[i]=2.0f * GL_PI * float(i+1)/float(10);
    }

    //ОДНЫ УРД ТАЛЫГ БАЙГУУЛНА.
    for(int i=0; i<10; i+=2){
        glBegin(GL_TRIANGLE_FAN);

        float angle_short1 = 2.0f * GL_PI * float(i-1)/float(10);
        float angle_long = 2.0f * GL_PI * float(i)/float(10);
        float angle_short2 = 2.0f * GL_PI * float(i+1)/float(10);

        float x1 = rad_small * cos(angle_short1);
        float y1 = rad_small * sin(angle_short1);
        float x = rad_big * cos(angle_long);
        float y = rad_big * sin(angle_long);
        float x2 = rad_small * cos(angle_short2);
        float y2 = rad_small * sin(angle_short2);

        float normal_tr1[3], normal_tr2[3];
        float vertices_tr1[3][3] = {{ -x,  -y, 0},
                                    {-x2, -y2, 0},
                                    { 0,  0, 10}};
        float vertices_tr2[3][3] = {{-x1, -y1, 0},
                                    { -x,  -y, 0},
                                    { 0,  0, 10}};

        //calcNormal(vertices_tr1, normal_tr1);
        //calcNormal(vertices_tr2, normal_tr2);

        //glNormal3fv(normal_tr1);
        //glNormal3fv(normal_tr2);

        glVertex3fv(vertices_tr1[0]);
        glVertex3fv(vertices_tr1[1]);
        glVertex3fv(vertices_tr1[2]);

        glVertex3fv(vertices_tr2[0]);
        glVertex3fv(vertices_tr2[1]);
        glVertex3fv(vertices_tr2[2]);

        glEnd();
    }

    //ОДНЫ АРД ТАЛЫГ БАЙГУУЛНА.
    glRotatef(180, 0.0f, 1.0f, 0.0f);
     for(int i=0; i<10; i+=2){
        glBegin(GL_TRIANGLE_FAN);

        float angle_short1 = 2.0f * GL_PI * float(i-1)/float(10);
        float angle_long = 2.0f * GL_PI * float(i)/float(10);
        float angle_short2 = 2.0f * GL_PI * float(i+1)/float(10);

        float x1 = rad_small * cos(angle_short1);
        float y1 = rad_small * sin(angle_short1);
        float x = rad_big * cos(angle_long);
        float y = rad_big * sin(angle_long);
        float x2 = rad_small * cos(angle_short2);
        float y2 = rad_small * sin(angle_short2);

        float normal_tr1[3], normal_tr2[3];
        float vertices_tr1[3][3] = {{ x,  y, 0},
                                    {x2, y2, 0},
                                    { 0,  0, 10}};
        float vertices_tr2[3][3] = {{x1, y1, 0},
                                    { x,  y, 0},
                                    { 0,  0, 10}};

        //calcNormal(vertices_tr1, normal_tr1);
        //calcNormal(vertices_tr2, normal_tr2);

        //glNormal3fv(normal_tr1);
        //glNormal3fv(normal_tr2);

        glVertex3fv(vertices_tr1[0]);
        glVertex3fv(vertices_tr1[1]);
        glVertex3fv(vertices_tr1[2]);

        glVertex3fv(vertices_tr2[0]);
        glVertex3fv(vertices_tr2[1]);
        glVertex3fv(vertices_tr2[2]);

        glEnd();
    }
}

void drawSunAndRadiation() {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    //glColor3f(1.0f, 1.0f, 0.0f);// Sun color (yellow)
    glColor3f(78/255.0, 149/255.0, 37/255.0);

    // Draw the sun
    glPushMatrix();
    glTranslatef(0, 1, -3);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glScalef(scale, scale, scale);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    //gluSphere(quadric, sunRadius, 20, 20);
    gluCylinder(quadric, 0.05, 0.4, 0.8, 100, 1);

    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.05*2 ,0.4*1.35, 0.8, 100, 1);

    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.05*2*2, 0.4*1.35*1.35, 0.8, 100, 1);

    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.05*2*2*1.5, 0.4*1.35*1.35*1.25, 0.8, 100, 1);

    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.05*2*2*1.5*1.1, 0.4*1.35*1.35*1.25*1.2, 0.8, 100, 1);

    glTranslatef(0, 0, -2);
    gluCylinder(quadric, 0.05, 0.1, 3.4, 100, 1);

    glTranslatef(0, 0, -0.5);
    glColor3f(206/255.0, 230/255.0, 243/255.0);

    RenderStar();

    glPopMatrix();

    // Draw solar radiation
    /*glPushMatrix();
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(-(double)i*45.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, -sunRadius, 0.0);
        glTranslatef(0.0, sunRadius, sunRadius*0.5);
        gluCylinder(quadric, sunRadius/3, 0.0, sunRadius * 2.5, 20, 20);
        glPopMatrix();
    }
    glPopMatrix();*/

    gluDeleteQuadric(quadric);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -5.0);

    initLighting();

    drawSunAndRadiation();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


/*void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        sunRadius += 0.1f;
        break;
    case '-':
        sunRadius -= 0.1f;
        if (sunRadius < 0.1f) sunRadius = 0.1f;
        break;
    }
    glutPostRedisplay();
}*/


void keyboard(unsigned char key, int x, int y){
    switch(key){
    case '+':
        scale += 0.1f;
        break;
    case '-':
        scale -= 0.1f;
        if(scale < 0.1f) scale=0.1f;
        break;
    }
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);

    glutPostRedisplay();
}

bool isDragging = false;
int prevMouseX;
int prevMouseY;

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            prevMouseX = x;
            prevMouseY = y;
        } else if (state == GLUT_UP) {
            isDragging = false;
        }
    }
}

void motion(int x, int y) {
    if (isDragging) {
        int dx = x - prevMouseX;
        int dy = y - prevMouseY;

        xRot += dy;
        yRot += dx;

        prevMouseX = x;
        prevMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar Radiation Example");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
