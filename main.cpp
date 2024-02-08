#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"
#include "BmpLoader.h"
#include <cmath>

double Txval=0,Tyval=0,Tzval=0;

////default
double eyeX=40, eyeY=10, eyeZ=150, refX = 55, refY=10,refZ=0;

int sky_texture=29;
//elevator
//double eyeX=40, eyeY=40, eyeZ=40, refX = 0, refY=30,refZ=0;

double windowHeight=1080, windowWidth=1080;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean liftUp = false, liftDown = true;
unsigned int ID;

double door_anglex=0,door_angley=180, left_door_x=38, right_door_x1=62.7, elevator_door=0, elevator_floor=0, lift_y=0;


bool doorOpen=false, doorClose=true;
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte quadIndices[1][4] =
{
    {0, 3, 2, 1}
};

static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cubeColor(float x, float y, float z, float a, float b, float c, int shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { x, y, z, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1, 1,1 , 1.0 };
    GLfloat mat_shininess[] = {shine};
//front phase niye kaaj hoche
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidCube(3);

}

void cube(float x, float y, float z)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { x, y, z, 1.0 };
    GLfloat mat_diffuse[] = { 0.6, 0.0, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1, 1,1 , 1.0 };
    GLfloat mat_shininess[] = {60};
//front phase niye kaaj hoche
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

   glutSolidCube(3);

}


static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

void drawCube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ,
    GLfloat shine=50){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
        v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
        v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][0]][0]);glTexCoord2f(1,1);
            glVertex3fv(&v_cube[c_ind[i][1]][0]);glTexCoord2f(1,0);
            glVertex3fv(&v_cube[c_ind[i][2]][0]);glTexCoord2f(0,0);
            glVertex3fv(&v_cube[c_ind[i][3]][0]);glTexCoord2f(0,1);
        }
    }
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ,
    GLfloat shine = 50, GLint slices = 30, GLint stacks = 30) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };\
    GLfloat mat_shininess[] = { shine };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidSphere(1.0, slices, stacks);
}


void table()
{
    // Top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    //glRotatef(0, 1 , 0, 0);
    glScalef(5.0, 0.1, 4.0);
    //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leg-front-right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0.5,-2.5, 0.5);
    glScalef(0.2, 2.5, 0.2);
    //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leg-front-left
    glPushMatrix();
    glTranslatef(4,-2.5, 0.5);
    glScalef(0.2, 2.5, 0.2);
    //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //leg-back right
    glPushMatrix();
    glTranslatef(0.5,-2.5, 3.5);
    glScalef(0.2, 2.5, 0.2);
    //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //leg
    glPushMatrix();
    glTranslatef(4,-2.5, 3.5);
    glScalef(0.2, 2.5, 0.2);
    //cubeColor(0.3, 0.2, 0.5, 0.3, 0.2, 0.5,60);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

}




void light0()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -5.0, 00.0, 0.0, 1.0 };

    glEnable( GL_LIGHT0);

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

}


void light1()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 30.0, 50.0, 0.0, 1.0 };

    glEnable( GL_LIGHT1);

    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 35.0);
}


void light2()
{
    // Directional light pointing in the negative z-direction
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -10.0, 10.5, 0.0, 0.0 };
    GLfloat light_direction[] = { 0.0, -1.0, 0.0 };

    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position);

    // Set the directional light parameters
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction);

    glEnable(GL_LIGHT2);
}

void mirror(){

    //00
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(0, 10, 198.7);
    glScalef(40, 35, 0.7);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();





    //white border left-bottom
    glPushMatrix();
    glTranslatef(0, 0, 199.2);
    glScalef(40, 10, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //white border left-bottom windows
    glPushMatrix();
    glTranslatef(0, 27.5, 199.2);
    glScalef(40, 0.8, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    // left |
    glPushMatrix();
    glTranslatef(20, 10, 199.2);
    glScalef(0.8, 35, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

}


void entrance(){
    //white border ______
    glPushMatrix();
    glTranslatef(40, 35, 199.5);
    glScalef(50, 1, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


     //white border | left
    glPushMatrix();
    glTranslatef(40, 0, 199.5);
    glScalef(1, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    //white border | right
    glPushMatrix();
    glTranslatef(90, 0, 199.5);
    glScalef(1, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


     //white border middle |
    glPushMatrix();
    glTranslatef(65, 35, 200);
    glScalef(1, 9, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();





    //create left windows on entrance
    glPushMatrix();
    mirror();
    glPopMatrix();

    //create right windows on entrance
    glPushMatrix();
    glTranslatef(90.5, 0, 0);
    glScalef(0.97,1,1);
    mirror();
    glPopMatrix();



    //white border leftmost |
    glPushMatrix();
    glTranslatef(0, 0, 199.5);
    glScalef(1, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    //white border | rightmost
    glPushMatrix();
    glTranslatef(129, 0, 199.5);
    glScalef(1, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();






}





void product(){
    //16-20
    int n = 16;
    for(float i=1; i<47; i+=2.08){

        for(int j=0; j<1; j+=1){
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,n);
            glTranslatef(i, 0, 118.4-j*0.25);
            glRotated(-15, 1, 0, 0);
            glScalef(2, 2, 0.25);
            drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();

        }
        n+=1;
        if(n>20) n=16;
    }
}


void chocolates(float width=5, float height=47){
    //16-20
    int n = 20;
    for(float k=0;k<0.4;k+=0.11){
        for(float i=1; i<height; i+=2.08){
            for(int j=0; j<width; j+=1){
                glPushMatrix();
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,n);
                glTranslatef(i, k, 118.2-j*0.55);
                glScalef(2, 0.1, 0.75);
                drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
                glDisable(GL_TEXTURE_2D);
                glPopMatrix();

            }
            if(n==20) n=21;
            else n=20;
        }
    }
}

void door(){

    //door_angle=0, left_door_x=38, right_door_x1=50.45, right_door_x1=62.7,
    glPushMatrix();
    glTranslatef(38, 0, 99.4);
    glRotatef(-1*door_anglex, 0, 1, 0);
    glScalef(12, 17.3, 0.5);
    drawCube(1, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glTranslatef(38, 18, 99.4);
    glScalef(12, 5, 0.5);
    drawCube(1, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glTranslatef(50.2, 18, 99.4);
    glScalef(12, 5, 0.5);
    drawCube(1, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    glPushMatrix();

    //closed
    //glTranslatef(50.45, 0, 99.4);
    //open
    glTranslatef(62.5, 0, 99.4);
    glRotatef(180+door_anglex, 0, 1, 0);
    glScalef(12.5, 17.3, 0.5);
    drawCube(1, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();
}


void shelf(){

    //first shelf rack___
    glPushMatrix();
    glTranslatef(0, 13.5, 90.7);
    glScalef(50, 0.4, 3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    //___
    glPushMatrix();
    glTranslatef(0, 9, 90.7);
    glScalef(50, 0.4, 3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //---
    glPushMatrix();
    glTranslatef(0, 4.5, 90.7);
    glScalef(50, 0.4, 3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //___
    glPushMatrix();
    glTranslatef(0, 0, 90.7);
    glScalef(50, 1, 3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //red stripe 3
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(0, 13.5, 93.72);
    glScalef(50, 0.6, 0);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //red stripe 2
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(0, 9, 93.72);
    glScalef(50, 0.6, 0);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //red stripe 1
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(0, 4.5, 93.72);
    glScalef(50, 0.6, 0);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //red stripe down 0
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(0, 0, 93.72);
    glScalef(50, 1, 0);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //red stripe left down
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(-0.01, 0, 90);
    glScalef(0, 1, 3.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //red stripe left up
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(-0.01, 0, 90);
    glScalef(0, 15, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //red stripe right up
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(50.01, 0, 90);
    glScalef(0, 15, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //red stripe right down
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    glTranslatef(50.01, 0, 90);
    glScalef(0, 1, 3.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //spine
    glPushMatrix();
    glTranslatef(0, 0, 90);
    glScalef(50, 15, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();



    // TO DO
    glPushMatrix();
    glTranslatef(0, 1.5, -25);
    product();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.2, -25);
    product();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 9.4, -25);
    product();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 14.32, -25);
    chocolates();
    glPopMatrix();

}


void double_shelf(){
    glPushMatrix();
    shelf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 0, 180.2);
    glRotatef(180, 0, 1, 0);
    shelf();
    glPopMatrix();
}

void base(){

    //back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glScalef(200, 110, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //up
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(0,45,0);
    glRotatef(90, 1, 0, 0);
    glScalef(200, 200, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //floor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(0,0,0);
    glRotatef(90, 1, 0, 0);
    glScalef(200, 200, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //left
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0, 0, 20);
    glRotatef(-90, 0, 1, 0);
    glScalef(180, 110, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(200, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(200.0, 110, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(0, 45, 199.8);
    glScalef(200.0, 70, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    //entrance
    glPushMatrix();
    glTranslatef(35, 0, 0);
    entrance();
    glPopMatrix();




    //shop concrete outline
    glPushMatrix();
    glTranslatef(-10,-0.1,-10);
    glRotatef(90, 1, 0, 0);
    glScalef(220, 220, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    //grass outside
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(-1500,-0.17,-1500);
    glRotatef(90, 1, 0, 0);
    glScalef(3000, 3000, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    //wall left of entrance
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0, 0, 199.2);
    glScalef(35, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //wall right of entrance
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(165, 0, 199.2);
    glScalef(35, 45, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void base2(){
    //front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0, -25, 199);
    glScalef(200, 70, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //left above lift
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(0, 20, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(20, 20, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //up
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(0,40.5,0);
    glRotatef(90, 1, 0, 0);
    glScalef(200, 200, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //floor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(0,-24.5,-0.1);
    glRotatef(90, 1, 0, 0);
    glScalef(200, 200, 0.8);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void place_shelves(){


    for(int i=10; i>-31; i-=10){
        //LEFT
        glPushMatrix();
        glTranslatef(10, 0, (i<-11?10:i));
        glScalef(0.5, 0.9, 0.5);
        double_shelf();
        glPopMatrix();

        //right
        glPushMatrix();
        glTranslatef(60, 0, i);
        glScalef(0.5, 0.9, 0.5);
        double_shelf();
        glPopMatrix();
    }

    //left wall shelf


    for(int i=25.5; i<100; i+=22){
        //left wall shelf
        glPushMatrix();
        glTranslatef(-90, 0, (i+20>=90?80:i+10));
        glRotatef(90, 0, 1, 0);
        glScalef(0.5, 1.2, 1);
        shelf();
        glPopMatrix();


        //right wall shelf
        glPushMatrix();
        glTranslatef(190, 0, i-23);
        glRotatef(-90, 0, 1, 0);
        glScalef(0.5, 1.2, 1);
        shelf();
        glPopMatrix();

    }

    glPushMatrix();
    glTranslatef(-90, 0, 99.5);
    glRotatef(90, 0, 1, 0);
    glScalef(0.5, 1.2, 1);
    shelf();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(190, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.5, 1.2, 1);
    shelf();
    glPopMatrix();





}


void chocolate_box(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(30, 0, 119);
    glScalef(5, 7, 5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(35.5, 0, 119);
    glScalef(5, 7, 5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}




void pc(){
    //monitor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glTranslatef(30, 10, 133.65);
    glRotatef(30, 1, 0, 0);
    glScalef(3, 2.5, 0.1);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //stand
    glPushMatrix();
    glTranslatef(31, 9.5, 134);
    glRotatef(-10, 1, 0, 0);
    glScalef(1, 1, 0.1);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glTranslatef(30, 9, 132.3);
    glScalef(3, 0.8, 2.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void fruits(double r, double g, double b){
    for(double k=11;k<21;k+=1){
        for(double i=9.8, j=121.55; i<=8, j<=125.47;i-=0.3, j+=1){
            glPushMatrix();
            glTranslatef(k, i, j);
            glRotatef(22, 1, 0, 0);
            glScalef(0.5, 0.5, 0.5);
            drawSphere(r, g, b,0.6, 0.6, 0.4);
            glPopMatrix();
        }
    }
}




void fruit_shelf(){

    //shelf base
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glTranslatef(10, 0, 119);
    glScalef(100, 7, 7);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //angled top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glTranslatef(9.95, 7, 119);
    glRotatef(22, 1, 0, 0);
    glScalef(100.1, 3, 10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //angled boards up #
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glTranslatef(10, 9.8, 120.2);
    glRotatef(22, 1, 0, 0);
    glScalef(100, 0.5, 0.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //angled boards down#
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glTranslatef(10, 6.2, 128.94);
    glRotatef(22, 1, 0, 0);
    glScalef(100, 0.5, 0.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //angled boards down#
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);
    glTranslatef(10, 8, 124.57);
    glRotatef(22, 1, 0, 0);
    glScalef(100, 0.5, 0.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();






    for(int i=10;i<=110;i+=10){
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,15);
        glTranslatef(i, 9.8, 120.2);
        glRotatef(22, 1, 0, 0);
        glScalef(0.5, 0.5, 10);
        drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    float red[] = {0.99, 0.97, 0.68, 0.26, 0.94};
    float green[] = {0.4, 0.06, 1, 0.74, 0.09};
    float blue[] = {0, 0.01,0, 0, 0, 0.01};

    int rgb_ind=0;
    for(double i=1; i<100; i+=10){
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glScalef(0.93, 1, 1);
        fruits(red[rgb_ind], green[rgb_ind], blue[rgb_ind]);
        rgb_ind+=1;
        rgb_ind%=sizeof(red) / sizeof(red[0]);
        glPopMatrix();

        int sec_row = (rgb_ind+1)%(sizeof(red) / sizeof(red[0]));
        glPushMatrix();
        glTranslatef(i, -1.8, 4.5);
        glScalef(0.93, 1, 1);
        fruits(red[sec_row], green[sec_row], blue[sec_row]);
        glPopMatrix();
    }

}


void cash_counter(){

    //|...:
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(30, 0, 115);
    glScalef(7, 7.5, 14);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //:__:
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(37, 1, 124);
    glScalef(15, 6.5, 5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //:...|
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(52, 0, 119);
    glScalef(7, 7.5, 10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //white top
    glPushMatrix();
    glTranslatef(29.5, 7.6, 123.5);
    glScalef(30.5, 0.3, 5.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();



    //white bottom left
    glPushMatrix();
    glTranslatef(29.5, 0, 114.5);
    glScalef(8, 0.3, 15);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    //white bottom right
    glPushMatrix();
    glTranslatef(51.5, 0, 118.5);
    glScalef(8, 0.3, 11);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    //pc
    glPushMatrix();
    glTranslatef(0,-0.9,-8);
    glScalef(1.4,1,1);
    pc();
    glPopMatrix();



}

void surroundings(){

    //road
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glTranslatef(-60, 0, 160);
    glScalef(300, 0.1, 20);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //shop brick concrete outline
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(-50, -0.08, -40);
    glScalef(200, 0.1, 200);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //fence back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glTranslatef(-50, 0, -40);
    glScalef(200, 10, 1);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //fence left
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glTranslatef(-50, 0, -40);
    glScalef(1, 10, 200);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //fence right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glTranslatef(150, 0, -40);
    glScalef(1, 10, 200);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}



void petrol_pump(){
    //head red
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(20, 12.25, 140);
    glScalef(7, 4, 1.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //head display
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glTranslatef(20.75, 2.25, 140);
    glScalef(5.5, 10, 1.4);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //head red
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glTranslatef(20, 0, 140);
    glScalef(7, 2, 1.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


void ac(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(20, 19, 1);
    glScalef(8,2.5,2);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(70, 19, 1);
    glScalef(8,2.5,2);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}



void signs(){
    glPushMatrix();
    glTranslatef(60, 22.2, 120);
    glScalef(0.3,2,0.3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(67.7, 22.2, 120);
    glScalef(0.3,2,0.3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,24);
    glTranslatef(60, 19, 120);
    glScalef(8,3.5,0.3);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}




void wall_lights(){
    glPushMatrix();
    glTranslatef(51, 23.6, 116);
    glScalef(16,0.3,23);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(84, 23.6, 90);
    glScalef(16,0.3,23);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(33.5, 23.6, 64);
    glScalef(16,0.3,23);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(84, 23.6, 41);
    glScalef(16,0.3,23);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glPopMatrix();

}





void icefreezer(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,25);
    glScalef(10,7,5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,26);
    glTranslatef(0, 7.05, 0);
    glScalef(10,0.01,5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}



void colafreezer(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(7,15,2.5);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glTranslatef(0, 0, 2.51);
    glScalef(7,15,0.01);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void foodfreezer(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
    glScalef(25,20,2);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
    glTranslatef(25, 0, 0);
    glScalef(25,20,2);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,27);
    glTranslatef(50, 0, 0);
    glScalef(25,20,2);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void display1st(){


    //first floor
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    base();
    glPopMatrix();

    glPushMatrix();
    place_shelves();
    glPopMatrix();




    glPushMatrix();
    door();
    glPopMatrix();

    glPushMatrix();
    surroundings();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(190, 0, 60);
    glRotatef(-90, 0, 1, 0);
    glScalef(0.5,1,1);
    cash_counter();
    glPopMatrix();


    for(int i=0; i>-30; i-=10){
        glPushMatrix();
        glTranslatef(20, 0, -45+i);
        glScalef(0.8, 0.8, 0.8);
        chocolate_box();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(43, 5.5, -65+i);
        chocolates(5,5);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(47.6, 5.5, -65+i);
        chocolates(5,5);
        glPopMatrix();
    }



    glPushMatrix();
    petrol_pump();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-3.5,0, -107);
    glScalef(0.87, 0.9, 0.9);
    fruit_shelf();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(60, 0, 0);
    petrol_pump();
    glPopMatrix();

    glPushMatrix();
    ac();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-17, -1.6, -50);
    signs();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-17, -1.6, -40);
    wall_lights();
    glPopMatrix();


}




void elevator(){

    //back
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(-10, lift_y, 0);
    glScalef(10,22.5,0.01);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //left
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(-10, lift_y, 0);
    glScalef(0.01,22.5,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    //front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(-10, lift_y, 10);
    glScalef(10,22.5,0.01);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //door
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(0, elevator_door, 0);
    glScalef(0.01,22.5,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //bottom
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(-10, lift_y, 0);
    glScalef(10,0.01,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(-10, lift_y+22.5, 0);
    glScalef(10,0.01,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //Elevator closed
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(0, (lift_y==0?22.5:0), 0);
    glScalef(0.01,22.5,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




}

void drawCylinder(float radius, float height, int slices) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluCylinder(quad, radius, radius, height, slices, 1);
    gluDeleteQuadric(quad);
}

void drawPizza() {
    glColor3f(1.0, 0.8, 0.0); // Set color to represent pizza crust

    // Draw pizza crust (a sphere)
    glutSolidSphere(1.0, 100, 100);

    // Draw pizza toppings (cylinders for simplicity)
    glColor3f(1.0, 0.0, 0.0); // Set color to represent pepperoni

    for (float angle = 0; angle < 360; angle += 30.0) {
        float radian = angle * 3.14159 / 180.0;
        float x = 0.6 * cos(radian);
        float y = 0.6 * sin(radian);

        glPushMatrix();
        glTranslatef(x, y, 0.1); // Adjust the z-coordinate for the toppings
        drawCylinder(0.2, 0.1, 50); // Draw a pepperoni (cylinder)
        glPopMatrix();
    }
}


void display2nd(){



    //spotlight
    glPushMatrix();
    glTranslatef(99, 20, 98.5);
    drawPizza();
    glPopMatrix();


    //second floor
    glPushMatrix();
    glTranslatef(0, 35, 0);
    glScalef(0.5, 0.5, 0.5);
    base2();
    glPopMatrix();


    glPushMatrix();
    elevator();
    glPopMatrix();


    //left wall freezer
    glPushMatrix();
    glTranslatef(-0.3, 22.5, 100);
    glRotatef(90, 0, 1, 0);
    //elevator();
    foodfreezer();
    glPopMatrix();


    /*
    //back wall freezer
    glPushMatrix();
    glTranslatef(10, 22.5, 0);
    foodfreezer();
    glPopMatrix();
    */


    //right wall freezer
    glPushMatrix();
    glTranslatef(99, 22.5, 0);
    glRotatef(-90, 0, 1, 0);
    glScalef(1.32, 1.2, 1);
    foodfreezer();
    glPopMatrix();


    for(float i=85.5; i>10; i-=10.1){
        glPushMatrix();
        glTranslatef(i, 22.5, 0);
        glScalef(1.3, 1.3, 1.3);
        colafreezer();
        glPopMatrix();
    }



    for(float i=30; i<80; i+=10.2){
        glPushMatrix();
        glTranslatef(40, 22.5,i);
        glScalef(1, 1.2, 2);
        icefreezer();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(50.2, 22.5,i+10);
        glRotatef(90, 0, 1, 0);
        glScalef(1, 1.2, 2);
        icefreezer();
        glPopMatrix();
    }




    glPushMatrix();
    glTranslatef(0, 30, 0);
    ac();
    glPopMatrix();
}


void sky(){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,sky_texture);
    //glTranslatef(30, 0, 120);
    glScalef(10,10,10);
    drawCube(0.8, 0.9, 0.9,0.6, 0.6, 0.4);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void round_sky(){
    glPushMatrix();
    //glTranslatef(-300, -100, -100);
    glTranslatef(30, 0, 120);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 0, 120);
    glRotatef(-20, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(49, 0, 123);
    glRotatef(-30, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(56, 0, 128);
    glRotatef(-45, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(62.55, 0, 134);
    glRotatef(-60, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(67.45, 0, 142);
    glRotatef(-70, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(70.5, 0, 150);
    glRotatef(-80, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(72, 0, 160);
    glRotatef(-90, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(72, 0, 170);
    glRotatef(-100, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(70.5, 0, 180);
    glRotatef(-110, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(66.5, 0, 190);
    glRotatef(-120, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(62, 0, 198);
    glRotatef(-130, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55.5, 0, 205.525);
    glRotatef(-140, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(48, 0, 212);
    glRotatef(-150, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 0, 216.6);
    glRotatef(-160, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31, 0, 219.5);
    glRotatef(-170, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22, 0, 221.1);
    glRotatef(-180, 0, 1, 0);
    glScalef(1, 1, 0.05);
    sky();
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90, 1, 0.09, 100000000);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,refX,refY,refZ,0,1,0);;

    glViewport(0, 0, 1900, 1000);

    glPushMatrix();
    glScalef(0.7, 1.1, 1);
    display1st();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.7, 1.1, 1);
    display2nd();
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(-10, 0, -40);
//    glScalef(10, 10, 1);
//    round_sky();
//    glPopMatrix();


    glPushMatrix();
    glTranslatef(-400, 0, -400);
    glScalef(80, 80, 0.1);
    sky();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-400, 0, -400);
    glRotatef(-90, 0, 1, 0);
    glScalef(80, 80, 0.1);
    sky();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(400, 0, -400);
    glRotatef(-90, 0, 1, 0);
    glScalef(80, 80, 0.1);
    sky();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(400, 0, 400);
    glRotatef(-180, 0, 1, 0);
    glScalef(80, 80, 0.1);
    sky();
    glPopMatrix();



    glFlush();
    glutSwapBuffers();

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'y':
        //double door_angle=0, left_door_x=38, right_door_x1=50.45, right_door_x1=62.7;
        if(doorClose) doorClose=false, doorOpen=true;
        else if(doorOpen) doorClose=true, doorOpen=false;
        break;
    case '=':
        if(elevator_door==0) elevator_door=22.5;
        else elevator_door=0;
        break;

    case '-':
        if(liftDown) liftUp=true, liftDown=false;
        else if(liftUp) liftDown=true, liftUp=false;
        break;

    case '0': //back to default eye point and ref point
        eyeX=65, eyeY=50, eyeZ=90, refX = -10, refY=30,refZ=0;
        break;
    case '1':
        eyeX=17, eyeY=20, eyeZ=90, refX = 110, refY=30,refZ=0;
        break;
    case '2':
        //glDisable(GL_LIGHTING);
        light0();
        break;
    case '3':
        //glDisable(GL_LIGHTING);
        light2();
        break;
    case '4':
        eyeX=40, eyeY=10, eyeZ=150, refX = 55, refY=10,refZ=0;
        break;
    case '5':
        eyeX=40, eyeY=20, eyeZ=40, refX = -40, refY=30,refZ=0; //door open ground
        break;
    case '6':
        eyeX=-20, eyeY=20, eyeZ=60, refX = 40, refY=20,refZ=0; //lift working
        break;
    case '7':
        eyeX=40, eyeY=40, eyeZ=40, refX = 0, refY=30,refZ=0; //2nd floor view
        break;
    case '9':
        if(sky_texture==29) sky_texture=30;
        else sky_texture=29;
        break;

    case '8':
        light1();
    case 'w': // move eye point upwards along Y axis
        eyeY+=1.0;
        break;
    case 's': // move eye point downwards along Y axis
        eyeY-=1.0;
        break;
    case 'a': // move eye point left along X axis
        eyeX-=1.0;
        break;
    case 'd': // move eye point right along X axis
        eyeX+=1.0;
        break;
    case 'o':  //zoom out
        eyeZ+=1;
        break;
    case 'i': //zoom in
        eyeZ-=1;
        break;
    case 'q': //back to default eye point and ref point
            eyeX=100, eyeY=10, eyeZ=100, refX = 40, refY=10,refZ=0;
        break;
    case 'j': // move ref point upwards along Y axis
        refY+=1.0;
        break;
    case 'n': // move ref point downwards along Y axis
        refY-=1.0;
        break;
    case 'b': // move ref point left along X axis
        refX-=1.0;
        break;
    case 'm': // move eye point right along X axis
        refX+=1.0;
        break;
    case 'k':  //move ref point away from screen/ along z axis
        refZ+=1;
        break;
    case 'l': //move ref point towards screen/ along z axis
        refZ-=1;
        break;

    case 27:    // Escape key
        exit(1);
    }
    glutPostRedisplay();
}

void animate()
{

    if(doorClose){
        door_anglex+=5;
        door_anglex=(door_anglex>=90?90:door_anglex);
    }
    if(doorOpen){
        door_anglex-=5;
        door_anglex=(door_anglex<=0?0:door_anglex);
    }
    if (liftUp){
        lift_y+=0.4;
        lift_y=(lift_y>=22.5?22.5:lift_y);
    }
    if(liftDown){
        lift_y-=0.2;
        lift_y=(lift_y<=0?0:lift_y);
    }

    glutPostRedisplay();

}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

static void idle(void)
{
    glutPostRedisplay();
}



int main (int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // glutInitWindowPosition(500, 200);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("SuperShop");


    //ceil
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\ceil.bmp");
    //wall
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\wall.bmp");
    //floor
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\floor.bmp");
    //swapno logo
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\swapno.bmp");
    //grass
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\grass.bmp");
    //window mirror 6
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\window.bmp");
    //red stripe for shelf 7
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\redstripe.bmp");
    //sale box 8
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\sale.bmp");
    //road 9
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\road.bmp");
    //concrete brick 10
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\brick.bmp");
    //concrete brick 11
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\fence.bmp");
    //pretrol pump lower 12
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\fuelpumplower.bmp");
    //pretrol pump upper 13
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\fuelpumpupper.bmp");
    //black 14
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\black.bmp");
    //wood 15
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\wood.bmp");
    //wood 16
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\noodles.bmp");
    //wood 17
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\kitten.bmp");
    //wood 18
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\chef.bmp");
    //wood 19
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\oat.bmp");
    //wood 20
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\chilli.bmp");
    //wood 21
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\choco1.bmp");
    //wood 22
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\choco2.bmp");
    //ac 23
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\ac.bmp");
    //signs 24
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\signs.bmp");
    //ice creAm 25
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\ice_cream.bmp");
    //freezer inside 26
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\freezer_inside.bmp");
    //frozen food 27
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\supershop\\bmp\\frozen_food.bmp");
    //colafreeze 28
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\CGIPL FINAL\\supershop\\bmp\\cola.bmp");
    //day_sky 29
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\CGIPL FINAL\\supershop\\bmp\\sky.bmp");
    //night sky 30
    LoadTexture("C:\\Users\\User\\Desktop\\CGIPL\\CGIPL FINAL\\supershop\\bmp\\nightsky.bmp");


    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);


    light0();


    //spot
    light1();
    light2();



    //glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutIdleFunc(animate);
     //glutIdleFunc(idle);

     //glClearColor(1,1,1,1);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glutMainLoop();

    return 0;
}
