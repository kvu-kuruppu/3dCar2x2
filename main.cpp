#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>


static float wheelRotate = 1.0;
float accelerate = 0.0;
float index1 = 0.0;
float index2 = 0.0;
GLfloat xt = 0.0, zt = 0.0;
float x = 0.0, y=0.0, z=0.0;
float lx=0.0, ly=0.0, lz=-1.0;
float angle=0.1;

void init()
{
    glClearColor(0.5, 0.8, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 0, 0.1f, 100.0f);
    glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1000.0, 1000.0);
}

void reshape(int w, int h){
    const float ar = (float) w / (float) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void doors(){
    glBegin(GL_POLYGON);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-4.0, 1.0, 0);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(-4.0, 2.5, 0);
    glVertex3f(-2.0, 3.0, 0);
    glVertex3f(3.0, 3.0, 0);
    glVertex3f(6.00, 2.5, 0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(6.00, 1.0, 0);

    glEnd();
}

void shutters(){
    glColor4f(0.6, 0.0, 0.0, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(-2.0, 3.0, 0);
    glVertex3f(3.0, 3.0, 0);
    glVertex3f(1.5, 4.0, 0);
    glVertex3f(-1.0, 4.0, 0);
    glEnd();
}

void headlights(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(6.01, 1.5, -0.5);
    glVertex3f(6.01, 1.8, -0.5);
    glVertex3f(6.01, 1.8, -0.9);
    glVertex3f(6.01, 1.5, -0.9);
    glEnd();

}

void reverseLights(){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-4.01, 1.2, -0.3);
    glVertex3f(-4.01, 1.6, -0.3);
    glVertex3f(-4.01, 1.6, -0.5);
    glVertex3f(-4.01, 1.2, -0.5);
    glEnd();
}

void wheels(){
    //frontWheelRight
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(3.5, 1.0, 0.0);
    glutWireTorus(0.3, 0.5, 20, 15);
    glPopMatrix();

    //rearWheelRight
    glPushMatrix();
    glTranslatef(-2.0, 1.0, 0.0);
    glutWireTorus(0.3, 0.5, 20, 15);
    glPopMatrix();

    //frontWheelLeft
    glPushMatrix();
    glTranslatef(3.5, 1.0, -4.0);
    glutWireTorus(0.3, 0.5, 20, 15);
    glPopMatrix();

    //rearWheelLeft
    glPushMatrix();
    glTranslatef(-2.0, 1.0, -4.0);
    glutWireTorus(0.3, 0.5, 20, 15);
    glPopMatrix();
}

void borders(){
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex3f(-2.05, 3.00, 0.05);
    glVertex3f(-1.05, 4.00, 0.05);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-2.05, 3.00, 0.05);
    glVertex3f(3.05, 3.00, 0.05);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(3.05, 3.00, 0.05);
    glVertex3f(1.55, 4.00, 0.05);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.05, 4.00, 0.05);
    glVertex3f(1.55, 4.00, 0.05);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.25, 3.00, 0.05);
    glVertex3f(0.25, 4.00, 0.05);
    glEnd();
}

void car()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glRotatef(index2, 0.0, 1.0, 0.0);
    //glTranslatef(xt,0,0);
    //glRotatef(index2, 0.0, 1.0, 0.0);


    //left and right doors
    glPushMatrix();
    doors();
    glTranslatef(0, 0, -4);
    doors();
    glPopMatrix();

    //front Side
    glBegin(GL_POLYGON);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(6.0, 1.0, 0);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(6.0, 2.5, 0);
    glVertex3f(6.0, 2.5, -4);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(6.0, 1.0, -4);

    glEnd();

    //rearSide1
    glBegin(GL_POLYGON);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-4.0, 1.0, 0);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(-4.0, 2.5, 0);
    glVertex3f(-4.0, 2.5, -4);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-4.0, 1.0, -4);

    glEnd();

    //rearSide2
    glBegin(GL_POLYGON);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(-4.0, 2.5, 0);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-2.0, 3.0, 0);
    glVertex3f(-2.0, 3.0, -4);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(-4.0, 2.5, -4);

    glEnd();

    //bonnet
    glBegin(GL_POLYGON);

    glColor3f(0.7, 0.0, 0.0);
    glVertex3f(6.0, 2.5, 0);
    glVertex3f(6.0, 2.5, -4);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 3.0, -4);
    glVertex3f(3.0, 3.0, 0);

    glEnd();

    //roof
    glBegin(GL_POLYGON);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(1.5, 4.0, 0);
    glVertex3f(1.5, 4.0, -4);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0, 4.0, -4);
    glVertex3f(-1.0, 4.0, 0);
    glEnd();

    //shutters
    glPushMatrix();
    shutters();
    glTranslatef(0,0,-4);
    shutters();
    glPopMatrix();

    //rearWindscreen
    glColor4f(0.6, 0.0, 0.0, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 4.0, 0);
    glVertex3f(-1.0, 4.0, -4);
    glVertex3f(-2.0, 3.0, -4);
    glVertex3f(-2.0, 3.0, 0);
    glEnd();

    //front windscreen
    glColor4f(0.6, 0.0, 0.0, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(1.5, 4.0, 0);
    glVertex3f(1.5, 4.0, -4);
    glVertex3f(3.0, 3.0, -4);
    glVertex3f(3.0, 3.0, 0);
    glEnd();

    //Headlights
    headlights();

    glPushMatrix();
    glTranslatef(0,0,-0.45);
    headlights();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-2.15);
    headlights();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-2.6);
    headlights();
    glPopMatrix();

    //Reverselights
    reverseLights();

    glPushMatrix();
    glTranslatef(0,0,-3.2);
    reverseLights();
    glPopMatrix();

    wheels();

    borders();

    glPushMatrix();
    glTranslatef(0, 0, -4.05);
    borders();
    glPopMatrix();

    //underCarriage
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-4.0, 1.0, 0);
    glVertex3f(-4.0, 1.0, -4);
    glVertex3f(6.0, 1.0, -4);
    glVertex3f(6.0, 1.0, 0);
    glEnd();
}

void road(){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.4, 0.0);
    glVertex3f(-10.0, 0.0, -10);
    glColor3f(0.4, 0.5, 0.2);
    glVertex3f(10.0, 0.0, -10);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 2);
    glColor3f(0.5, 0.5, 0.2);
    glVertex3f(-10.0, 0.0, 2);
    glEnd();
    glPopMatrix();

}

void trees(){
    for(int i=0; i<3; i++){
        glPushMatrix();
        glTranslated(0, 5+(i*3), -20);
        glRotated(-90, 1.0, 0, 0);
        glColor3f(0.5, 0.8, 0.0);
        glutSolidCone(9-(2*i), 5, 50, 50);
        glPopMatrix();
    }

    glPushMatrix();
    glColor3f(0.5,0.3,0.0);
    glTranslated(0,0,-20);
    glRotated(-90, 1.0, 0, 0);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1, 1, 5, 50, 50);
    glPopMatrix();
}

void grass(){
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-10.0, 0.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0, 0.0, -50);
    glVertex3f(10, 0.0, -50);
    glColor3f(1.0, 0.5, 0.1);
    glVertex3f(10.0, 0.0, 0);
    glEnd();
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(20+x, 15+y, 30+z,
              0, 0, 0,
              0.0, 1.0, 0.0);

    glRotatef(index1, 0.0, 2.0, 0.0);

    glPushMatrix();
    glTranslatef(xt,0,zt);
    glRotatef(index2, 0.0, 2.0, 0.0);
    glTranslatef(0,0,0);
    car();
    glPopMatrix();

    glPushMatrix();
    glScalef(60, 1, 1);
    road();
    glPopMatrix();

    for(int i=-5; i<5; i++){
        for(int j=-4; j<=0; j++){
            glPushMatrix();
            glTranslatef(i*35, 0, j*50);
            trees();
            glPopMatrix();
        }
        for(int j=1; j<6; j++){
            glPushMatrix();
            glTranslatef(i*35, 0, j*40);
            trees();
            glPopMatrix();
        }
    }

    glPushMatrix();
    glTranslatef(0, 0, -10.01);
    glScalef(50, 0, 50);
    grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 2.01);
    glScalef(50, 0, 50);
    glRotated(180, 0.0, 0.0, 1.0);
    glRotated(180, 0.0, 1.0, 0.0);
    grass();
    glPopMatrix();

    glutSwapBuffers();
}

void keyFunctions(int key, int x, int y)
{
    float fraction=0.5;
    switch (key)
    {
    case GLUT_KEY_UP :  //forward
        xt += 1.0;
        accelerate += wheelRotate;
        if(wheelRotate < 1000)
        {
            wheelRotate += 50;
        }
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN :    //backward
        xt -= 1.0;
        accelerate -= wheelRotate;
        if(wheelRotate > 0)
        {
            wheelRotate += 50;
        }
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    case GLUT_KEY_RIGHT:    //rotate right
        index1 += 5;
        break;
    case GLUT_KEY_LEFT:     //rotate left
        index1 -= 5;
        break;
    /*case GLUT_KEY_HOME:
        xt += 1.0;      //only car forward
        accelerate -= wheelRotate;
        if(wheelRotate < 1000)
        {
            wheelRotate += 50;
        }
        break;
    case GLUT_KEY_END:
        xt -= 1.0;      //only car forward
        accelerate -= wheelRotate;
        if(wheelRotate > 0)
        {
            wheelRotate += 50;
        }
        break;*/
    case GLUT_KEY_PAGE_UP :         // camera zoom in
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_PAGE_DOWN :       // camera zoom out
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'a':    //rotate right
            index2 += 5;
            break;
        case 'd':     //rotate left
            index2 -= 5;
            break;
        case 'w':
            xt += 1.0;
            if(index2 > 0 && index2 < 360){
                zt -= 1.0;
            }
            /*else if (index2>90 && index2 < 180){
                zt += 1.0;
            }
            /*else{
                }*/
            accelerate += wheelRotate;
            if(wheelRotate > 0)
            {
                wheelRotate += 50;
            }
            break;
        case 's':
            xt -= 1.0;
            //zt -= 1.0;
            accelerate -= wheelRotate;
            if(wheelRotate > 0)
            {
                wheelRotate += 50;
            }
            break;

    }
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(300,80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Enhanced Car");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyFunctions);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
