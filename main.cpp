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

int treeColor = 0;
int starColor = 0;
int selectedColor = 0;

GLfloat sunRadius = 0.3f;

GLuint ObjectList;
void ReduceToUnit(float vector[3]) {
    float length;
    length = (float)sqrt((vector[0] * vector[0]) +
                         (vector[1] * vector[1]) +
                         (vector[2] * vector[2]));
    if (length == 0.0f)
        length = 1.0f;
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}
void calcNormal(float v[3][3], float out[3]) {
    float v1[3], v2[3];
    static const int x = 0;
    static const int y = 1;
    static const int z = 2;
    v1[x] = v[0][x] - v[1][x];
    v1[y] = v[0][y] - v[1][y];
    v1[z] = v[0][z] - v[1][z];
    v2[x] = v[1][x] - v[2][x];
    v2[y] = v[1][y] - v[2][y];
    v2[z] = v[1][z] - v[2][z];
    out[x] = v1[y] * v2[z] - v1[z] * v2[y];
    out[y] = v1[z] * v2[x] - v1[x] * v2[z];
    out[z] = v1[x] * v2[y] - v1[y] * v2[x];
    ReduceToUnit(out);
}
void SetupRC(){
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.9078f, 0.9219f, 0.9529f, 0.9f); // background color - blue
}

void drawStar() {
    switch (starColor) {
        case 0:  // yellow 1
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        case 1:  // yellow 2
            glColor3f(241/255.0, 201/255.0, 59/255.0);
            break;
        case 2:  // yellow 3
            glColor3f(240/255.0, 222/255.0, 54/255.0);
            break;
        case 3:  // yellow 4
            glColor3f(1, 181/255.0, 52/255.0);
            break;
        default:
            glColor3f(254/255.0, 255/255.0, 134/255.0);  // Default yellow
    }

    float rad_big = 0.3f;
    float rad_small = 0.1f;

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
                                    { 0,  0, 0.1}};
        float vertices_tr2[3][3] = {{-x1, -y1, 0},
                                    { -x,  -y, 0},
                                    { 0,  0, 0.1}};
        calcNormal(vertices_tr1, normal_tr1);
        calcNormal(vertices_tr2, normal_tr2);
        glNormal3fv(normal_tr1);
        glNormal3fv(normal_tr2);
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
                                    { 0,  0, 0.1}};
        float vertices_tr2[3][3] = {{x1, y1, 0},
                                    { x,  y, 0},
                                    { 0,  0, 0.1}};
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
void drawTree(){
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    switch (treeColor) {
        case 0:  // green 1 - mint light
            glColor3f(0.0, 1.0, 171/255.0);
            break;
        case 1:  // green 2 - mint dark
            glColor3f(20/255.0, 195/255.0, 142/255.0);
            break;
        case 2:  // green 3 - pastel light
            glColor3f(193/255.0, 242/255.0, 176/255.0);
            break;
        case 3:  // green 4 - orginal
            glColor3f(101/255.0, 183/255.0, 65/255.0);
            break;
        default:
            glColor3f(30/255.0, 174/255.0, 152/255.0);  // Default Teal green - blue green
    }

    //Layer 1 - Top
    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0, 0.05, 0, 100, 1);
    gluCylinder(quadric, 0.05, 0.4, 0.8, 100, 1);
    //Layer 2
    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.05*2 ,0.4*1.35, 0.8, 100, 1);
    glTranslatef(0, 0, 0.3);
    gluCylinder(quadric, 0.4, 0, 0, 100, 1);
    //Layer 3
    glTranslatef(0, 0, 0.2);
    gluCylinder(quadric, 0.05*2*2, 0.4*1.35*1.35, 0.8, 100, 1);
    glTranslatef(0, 0, 0.3);
    gluCylinder(quadric, 0.4*1.35, 0, 0, 100, 1);
    //Layer 4
    glTranslatef(0, 0, 0.2);
    gluCylinder(quadric, 0.05*2*2*1.5, 0.4*1.35*1.35*1.25, 0.8, 100, 1);
    glTranslatef(0, 0, 0.3);
    gluCylinder(quadric, 0.4*1.35*1.35, 0, 0, 100, 1);
    //Layer 5
    glTranslatef(0, 0, 0.2);
    gluCylinder(quadric, 0.05*2*2*1.5*1.1, 0.4*1.35*1.35*1.25*1.2, 0.8, 100, 1);
    glTranslatef(0, 0, 0.3);
    gluCylinder(quadric, 0.4*1.35*1.35*1.25, 0, 0, 100, 1);
    glTranslatef(0, 0, 0.5);
    gluCylinder(quadric, 0.4*1.35*1.35*1.25*1.2, 0, 0, 100, 1);
    //Bottom - Wood
    glColor3f(108/255.0, 52/255.0, 40/255.0);
    glTranslatef(0, 0, -2);
    gluCylinder(quadric, 0.05, 0.1, 3, 100, 1);
    glTranslatef(0, 0, 2);
    gluCylinder(quadric, 0.1, 0, 0, 100, 1);

    glTranslatef(0, 0, -2.8);

    glColor3f(1 , 0 , 0);
    glTranslatef(0.8, -0.5, 3.2);
    glutSolidCube(0.5);

    glColor3f(0.91, 0.012, 0.922);
    glTranslatef(0, 1, 0);
    glutSolidCube(0.5);

    glColor3f(0.859, 0.8, 0.082);
    glTranslatef(-1.2, 0, 0);
    glutSolidCube(0.6);

    glColor3f(0.082, 0.318, 0.859);
    glTranslatef(0, -1.2, 0);
    glutSolidCube(0.4);

    glColor3f(0.082, 0.318, 0.859);
    glTranslatef(0.8, 0.5, -2.5);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(0.8, 0, 0);
    glTranslatef(-0.9, 0.2 , 0.4);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(0, 1, 1);
    glTranslatef(1.1, 0.2 , 0.4);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(1, 1, 0);
    glTranslatef(-0.8, -0.8 , 0);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(1, 0, 0);
    glTranslatef(0.2, 1.3 , 0.44);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(1,0 , 1);
    glTranslatef(0.2, -1.45 , 0.1);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(1,0 , 1);
    glTranslatef(0.2, 1.45 , 0.4);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(1,1 , 0);
    glTranslatef(0.5, -1 , 0.1);
    glutSolidSphere(0.1 , 24 , 24);

        glColor3f(0 ,0 , 1);
    glTranslatef(-1.8, 0 , 0.1);
    glutSolidSphere(0.1 , 24 , 24);

    glColor3f(0.5,0.1 , 0.5);
    glTranslatef(0.05, 0.4 , -0.5);
    glutSolidSphere(0.1 , 24 , 24);

    glPopMatrix();

    gluDeleteQuadric(quadric);
}
void drawSun(){
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glColor3f(1.0f, 1.0f, 0.0f); // Sun color (yellow)


    // Draw the sun
    glPushMatrix();
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glScalef(0.5, 1.0, 1.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluSphere(quadric, sunRadius, 20, 20);
    glPopMatrix();
    // Draw solar radiation
    glPushMatrix();
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
    glPopMatrix();
    gluDeleteQuadric(quadric);
}

void drawSnowman()
    {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // Save the matrix state and do the rotations
    glPushMatrix();
        // Move object back and do in place rotation
      //  glTranslatef(0.0f, -1.0f, -5.0f);

        // Main Body
        glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            gluSphere(quadric, .40f, 26, 13);  // Bottom

            glTranslatef(0.0f, .550f, 0.0f); // Mid section
            gluSphere(quadric, .3f, 26, 13);

            glTranslatef(0.0f, 0.45f, 0.0f); // Head
            gluSphere(quadric, 0.24f, 26, 13);

            // Eyes
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.1f, 0.1f, 0.21f);
            gluSphere(quadric, 0.02f, 26, 13);

            glTranslatef(-0.2f, 0.0f, 0.0f);
            gluSphere(quadric, 0.02f, 26, 13);

            // Nose
            glColor3f(1.0f, 0.3f, 0.3f);
            glTranslatef(0.1f, -0.12f, 0.0f);
            gluCylinder(quadric, 0.04f, 0.0f, 0.3f, 26, 13);
        glPopMatrix();

        // Hat
        glPushMatrix();
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.0f, 1.17f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadric, 0.17f, 0.17f, 0.4f, 26, 13);

            // Hat brim
            glDisable(GL_CULL_FACE);
            gluDisk(quadric, 0.17f, 0.28f, 26, 13);
            glEnable(GL_CULL_FACE);

            glTranslatef(0.0f, 0.0f, 0.40f);
            gluDisk(quadric, 0.0f, 0.17f, 26, 13);
        glPopMatrix();

    // Restore the matrix state
    glPopMatrix();


    }
void Render() {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glTranslatef(0, 0, -3);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glScalef(scale, scale, scale);
    //glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0, 1, 0);
    glRotatef(90, 0.0, 0.0, 1.0);
    //glRotatef(90, 0.0, 1.0, 0.0);
    drawStar();
    glRotatef(270, 0.0, -1.0, 0.0);
    glTranslatef(0.0, 0.0, -0.3);
    drawTree();
    glTranslatef(-5, 2, -5);
    drawSun();
    glRotatef(270, 1.0, 0.0, 0.0);
    glTranslatef(6, -6, 0);
    glRotatef(90, 0.0, 1.0, 0.0);
    drawSnowman();
    gluDeleteQuadric(quadric);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    Render();
    glutSwapBuffers();
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
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

void changeStarColor(int value) {
    starColor = value;
    glutPostRedisplay();
}
void changeTreeColor(int value) {
    treeColor = value;
    glutPostRedisplay();
}
void changeColor(int value) {
    selectedColor = value;
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Christmas");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    SetupRC();

    // menu - colors
    int starColors = glutCreateMenu(changeStarColor);
    glutAddMenuEntry("Yellow Light", 0);
    glutAddMenuEntry("Yellow + Brown", 1);
    glutAddMenuEntry("Yellow Dark", 2);
    glutAddMenuEntry("Orange", 3);

    int treeColors = glutCreateMenu(changeTreeColor);
    glutAddMenuEntry("Mint Light", 0);
    glutAddMenuEntry("Mint Dark", 1);
    glutAddMenuEntry("Pastel Light", 2);
    glutAddMenuEntry("Original", 3);

    // Main menu
    int mainMenu = glutCreateMenu(changeColor);
    glutAddSubMenu("Star", starColors);
    glutAddSubMenu("Tree", treeColors);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
