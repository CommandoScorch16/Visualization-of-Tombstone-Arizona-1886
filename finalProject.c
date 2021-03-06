//Samuel Horton
//CSCI 4229
//Assignment 6 "Lighting and Textures"
#include <stdio.h>
#include "CSCIx229.h"
#include <stdlib.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int axes=1;       //  Display axes
int mode=1;
int mode1=1;       //  Projection mode
int move=1;       //  Move light
int th=200;         //  Azimuth of view angle
int test = 200;
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=60.0;   //  Size of world
// Light values
int one       =   1;  // Unit value
int distance  =   80;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   2.7;  // Elevation of light

double Ox=0,Oy=0,Oz=0; //  LookAt Location
int X,Y;               //  Last mouse location
float z[65][65];       //  DEM data
float zmin=+1e8;       //  DEM lowest location
float zmax=-1e8;       //  DEM highest location
float zmag=1;          //  DEM magnification

char* groundTexture = "ground.bmp";
char* sky = "sky.bmp";
char* bc = "bc1.bmp";
unsigned int a;
unsigned int b;
unsigned int c;
unsigned int d;
unsigned int merman,door1,door2,sign1,f,g,h,i,j,k,l,wood1,wood2,wood3,wood4,wood5,face1,face2,face3,face4,face5,face6,face7;


unsigned int count = 0; //how many stores
int height = -22;
int upDown,leftRight=0;
double xxx = 0.0;
double zzz = 0.0;
int displayNames = 0;
unsigned int mman = 0;
#define LEN 8192  //  The maximum length of text string

static void skyBox(double D);

//Building Prototypes
void occidentalHotel(double sx, double sy, double sz, double theta, double tx, double ty, double tz);

static void birdCage(double sx, double sy, double sz, double theta, double tx, double ty, double tz);

static void store1(double sx, double sy, double sz, double theta, double tx, double ty, double tz);

static void saloon1(double sx, double sy, double sz, double theta, double tx, double ty, double tz);

static void smallHouse2(double sx, double sy, double sz, double theta, double tx, double ty, double tz);


void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void calculateNormal2(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3, double sign)
{


double r1x = x2-x1;
double r1y = y2-y1;
double r1z = z2-z1;

double r2x = x2-x3;
double r2y = y2-y3;
double r2z = z2-z3;


glNormal3f( sign*((r1y*r2z)-(r2y*r1z))  ,  sign*(-1*((r1x*r2z)-(r2x*r1z)))  ,  sign*((r1x*r2y)-(r2x*r1y)) );
}


void calculateNormal(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3)
{


int r1x = x2-x1;
int r1y = y2-y1;
int r1z = z2-z1;

int r2x = x2-x3;
int r2y = y2-y3;
int r2z = z2-z3;


glNormal3f( ((r1y*r2z)-(r2y*r1z))  ,  -1*((r1x*r2z)-(r2x*r1z))  ,  ((r1x*r2y)-(r2x*r1y)) );
}

void drawRoads()
{
printf("theta is %d", th);

/*
Street Widths:

Safford: 8
Freemont: 8
Allen: 7
Tough Nut: 6.5 

Block Sizes (Width x Height):
Below Safford: 28 x 28.5
Below Freemont: 28 x 28.5
Below Allen: 28 x 22
*/

int i, j;
double h = 0.1;
double streetWidth = 7.5;
//for each row
for (i = 0; i < 3; i++)
{
double x1, x2, y1, y2;


if (i == 0) {
x1 = y1 = 0;
x2 = 28.0;
y2 = 28.5;
}

else if (i == 1){
x1 = 0.0;
y1 = 36.5;
x2 = 28.0;
y2 = 65.0;
}

else if (i == 2){
x1 = 0.0;
y1 = 72.0;
x2 = 28.0;
y2 = 94.0;
}
        //draw each block in this row
	for (j = 0; j < 5; j++)
	
	{       //printf("x1 is %f, and x2 is %f\n",x1 ,x2);
        	
		glBegin(GL_QUADS);
		glColor3f(0,0.5,0.7);
		glVertex3f(x1,h,y1);
		glVertex3f(x2,h,y1);
 		glVertex3f(x2,h,y2);
		glVertex3f(x1,h,y2);
                glRasterPos3d(5.0,0.0,0.0);
		char place[25];
		sprintf(place,"%f,%f", x1,y1);
		//Print(place);
		Print("L");	
                
		double i1;
		for (i1 = 0.0; i1 < 5.0; i1++){
			
			if ((i == 0) && (j == 1) && (i1 == 1.0)){
			
			occidentalHotel(1.0,1.0,1.0,330.0,x2-2.6-i1*5,0.0,y2-4.0);
			
			}
			else if ((i == 0) && (j == 0) && (i1 == 4.0)){
			birdCage(0.8,0.8,0.8,180.0,x2-2-i1*5,0.0,y2);
			}
			else {
			//draw north side
			if (((int)i1)%2 == 0)
			smallHouse2(0.7,0.7,0.7,0.0,x2-3.5-i1*5,0.0,y2);
			else
			store1(0.5,0.5,0.5,180.0,x2-2-i1*5,0.0,y2);
			
			//draw east side
			if (((int)i1)%3 == 0)
			smallHouse2(0.7,0.7,0.7,270.0,x1,0.0,y1+i1*5);		
			else
			saloon1(0.5,0.5,0.5,90,x1,0.0,y1+i1*5.0);
			
			//draw west side
		
			//dont draw inside occidental
			if ((i != 0) && (j != 0) && (i1 != 0.0))
			smallHouse2(0.7,0.7,0.7,90.0,x2,0.0,y2-i1*5);
			
			//draw south side
			store1(0.5,0.5,0.5,0.0,x1+5+i1*5,0.0,y1+0);	
			}
		}
		double x0 = x1;
                x1 = x2 + streetWidth;
                x2 = (x2-x0) + x2 + streetWidth;

		

		glEnd();
	}


}
 

}

void drawBuildings()
{
/* 
int i;
for (i = 0; i < 5; i++)
smallHouse1(0.6,0.6,0.6,0.0,24.0-i*5,0.0,92.0);
*/

}

void DEM()
{
  
     // smallHouse1(0,0,0,45,-5,1,1);     

      //glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      
   
      
      //smallHouse1(1.0,1.0,1.0,45.0,3.0,0.0,3.0);

      
       
    


     //right, now tile the floor
      glBindTexture(GL_TEXTURE_2D, a);
      glBegin(GL_QUADS);
      int i;
      int j;
      int x1 = 174;
      int x2 = 168;
      int y1 = 174;
      int y2 = 168;
      for (j = 0; j<50;j++){
      y1 = 174;
      y2 = 168;
      for (i = 0; i<50; i++) {
      calculateNormal(x1,0,y1, x2,0,y1, x2,0,y2);
      glTexCoord2f(0,0); glVertex3d(x1,0,y1);
      glTexCoord2f(1,0); glVertex3d(x2,0,y1);
      glTexCoord2f(1,1); glVertex3d(x2,0,y2);
      glTexCoord2f(0,1); glVertex3d(x1,0,y2);
      y1-=6;
      y2-=6;
      }x1-=6;x2-=6;}
      glEnd();




      //glPopMatrix();
      glDisable(GL_TEXTURE_2D);

}




void occidentalHotel(double sx, double sy, double sz, double theta, double tx, double ty, double tz){

glPushMatrix();

glTranslated(tx,ty,tz);
glScaled(sx,sy,sz);
//glScaled(1.5,1.5,1.5);
glRotated(theta,0,1,0);


glBegin(GL_QUADS);

//draw right face
calculateNormal2(0.0,0.0,2.5,7.0,0.0,0.0,7.0,5.0,0.0,-1.0);
glVertex3f(0.0,0.0,2.5);
glVertex3f(7.0,0.0,0.0);
glVertex3f(7.0,5.0,0.0);
glVertex3f(0.0,5.0,2.5);

glEnd();

//draw top windows
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, g);
glBegin(GL_QUADS);

int now;
double x11=0;
double z11=2.5;

double x22=2;
double z22=-7.6;

for (now = 0; now < 5; now+=1)
{
calculateNormal2(x11,4.2,z11,x11+.5,4.2,z11-.2,x11+.5,3.2,z11-.2,1.0);
glTexCoord2f(0,1); glVertex3f(x11,4.2,z11);
glTexCoord2f(1,1); glVertex3f(x11+.5,4.2,z11-.2);
glTexCoord2f(1,0); glVertex3f(x11+.5,3.2,z11-.2);
glTexCoord2f(0,0); glVertex3f(x11,3.2,z11);

if (now != 0){
calculateNormal2(x22,4.2,z22,x22+.5,4.2,z22+.60,x22+.5,3.2,z22+.60,-1.0);
glTexCoord2f(0,1); glVertex3f(x22,4.2,z22);
glTexCoord2f(1,1); glVertex3f(x22+.5,4.2,z22+.60);
glTexCoord2f(1,0); glVertex3f(x22+.5,3.2,z22+.60);
glTexCoord2f(0,0); glVertex3f(x22,3.2,z22);
}

x11+=1.2;
z11-=.4;

x22+=1.2;
z22+=1.4;

}

glEnd();
glDisable(GL_TEXTURE_2D);

glBegin(GL_QUADS);
//draw front skinny face
calculateNormal2(7.0,0.0,0.0,7.3,0.0,-1.25,7.3,5.0,-1.25,-1.0);
glVertex3f(7.0,0.0,0.0);
glVertex3f(7.4,0.0,-1.25);//-1.25);
glVertex3f(7.4,5.0,-1.25);//-1.25);
glVertex3f(7.0,5.0,0.0);
glEnd();

//draw bottom door
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, door2);
glBegin(GL_QUADS);

calculateNormal2(7.1,0.0,-0.2,7.3,0.0,-0.9,7.3,1.5,-0.9,-1.0);
glTexCoord2f(0,0); glVertex3f(7.1,0.0,-0.2);
glTexCoord2f(1,0); glVertex3f(7.3,0.0,-0.9);
glTexCoord2f(1,1); glVertex3f(7.3,1.5,-0.9);
glTexCoord2f(0,1); glVertex3f(7.1,1.5,-0.2);

glEnd();
glDisable(GL_TEXTURE_2D);

//draw top door
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, door1);
glBegin(GL_QUADS);

calculateNormal2(7.1,0.0,-0.2,7.3,0.0,-0.9,7.3,1.5,-0.9,-1.0);
glTexCoord2f(0,0); glVertex3f(7.1,3.0,-0.2);
glTexCoord2f(1,0); glVertex3f(7.3,3.0,-0.9);
glTexCoord2f(1,1); glVertex3f(7.3,4.0,-0.9);
glTexCoord2f(0,1); glVertex3f(7.1,4.0,-0.2);
glEnd();
glDisable(GL_TEXTURE_2D);

glBegin(GL_QUADS);

//draw left face
calculateNormal2(7.4,0.0,-1.25,2.5,0.0,-7.0,2.5,5.0,-7.0,-1.0);
glVertex3f(7.4,0.0,-1.25);
glVertex3f(2.5,0.0,-7.0);
glVertex3f(2.5,5.0,-7.0);
glVertex3f(7.4,5.0,-1.25);

//draw back
calculateNormal2(2.5,0.0,-7.0,0.0,0.0,2.5,0.0,5.0,2.5,-1.0);
glVertex3f(2.5,0.0,-7.0);
glVertex3f(0.0,0.0,2.5);
glVertex3f(0.0,5.0,2.5);
glVertex3f(2.5,5.0,-7.0);


glEnd();


glBegin(GL_TRIANGLES);
//draw roof
calculateNormal2(7.0,5.0,0.0,2.5,5.0,-7.0,0.0,5.0,2.5,-1.0);
glVertex3f(7.0,5.0,0.0);
glVertex3f(2.5,5.0,-7.0);
glVertex3f(0.0,5.0,2.5);

calculateNormal2(7.4,5.0,-1.25,2.5,5.0,-7.0,7.0,5.0,0.0,-1.0);
glVertex3f(7.4,5.0,-1.25);
glVertex3f(2.5,5.0,-7.0);
glVertex3f(7.0,5.0,0.0);

glEnd();

glBegin(GL_QUADS);

//right balcony
calculateNormal2(0.0,3.0,2.5,8.5,3.0,-.545,9.5,3.0,0.0,1.0);
glVertex3f(0.0,3.0,2.5);
glVertex3f(8.5,3.0,-.545);
//glVertex3f(7.94,3.0,-.345);
//glVertex3f(7.0,3.0,0.0);
//glVertex3f(7.0,3.0,1.0);
glVertex3f(9.5,3.0,0);
glVertex3f(0.0,3.0,3.5);


//left balcony
calculateNormal2(2.5,3.0,-7.0,8.5,3.0,-.125,9.45,3.0,0.0,-1.0);
glVertex3f(2.5,3.0,-7.0);
glVertex3f(8.5,3.0,-.125);
//glVertex3f(7.94,3.0,-.625);
glVertex3f(9.45,3.0,0);
glVertex3f(3.2,3.0,-7.7);


//balcony bondo
calculateNormal2(7.55,3.0,-2,7.0,3.0,0.0,8,3.0,-1.0,-1.0);
glVertex3f(7.55,3.0,-2);//-1.25);
glVertex3f(7.0,3.0,0.0);
glVertex3f(8,3.0,-1.0);
glVertex3f(9.3,3.0,-0.1);


//right wall
double m;
double u = 0.0;
double z1 = 3.5;
double z2 = 3.46;
double z0 = 3.3;
for (m = 0.0; m < 24.0; m++){
calculateNormal2(u,3.0,z1,u+0.1,3.0,z2,u+0.1,3.5,z2,-1.0);
glVertex3f(u,3.0,z1);
glVertex3f(u+0.1,3.0,z2);
glVertex3f(u+0.1,3.5,z2);
glVertex3f(u,3.5,z1);

if (m != 23.0){
glVertex3f(u,3.4,z1);
glVertex3f(u+0.05,3.5,z1);
glVertex3f(u+0.51,3.2,z0);
glVertex3f(u+0.46,3.1,z0);

glVertex3f(u,3.2,z1);
glVertex3f(u+0.05,3.1,z1);
glVertex3f(u+0.51,3.4,z0);
glVertex3f(u+0.46,3.5,z0);
}

u += 0.4;
z1-=0.15;
z2-=0.15;
z0-=0.15;
}

//left wall
double m1;
double x = 3.2;
double z3 = -7.7;
double z5 = -7.6;
double z4 = -7.3;
for (m1 = 0.0; m1<24.0;m1+=1)
{

calculateNormal2(x,3.0,z3,x+0.1,3.0,z4,x+0.1,3.5,z4,1.0);
glVertex3f(x,3.0,z3);
glVertex3f(x+0.1,3.0,z5);
glVertex3f(x+0.1,3.5,z5);
glVertex3f(x,3.5,z3);

if (m1 != 23.0){
glVertex3f(x,3.4,z3);
glVertex3f(x+0.05,3.5,z3);
glVertex3f(x+0.5,3.2,z4);
glVertex3f(x+0.5,3.1,z4);


glVertex3f(x,3.2,z3);
glVertex3f(x+0.05,3.1,z3);
glVertex3f(x+0.5,3.4,z4);
glVertex3f(x+0.5,3.5,z4);
}
//glVertex3f(9.45,3.0,0);
x+=0.265;
z3+=0.326;
z4+=0.326;
z5+=0.326;
}

glEnd();

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, f);
glBegin(GL_QUADS);

//now draw the top sign
calculateNormal2(7.2,5.0,-1.35,6.8,5.0,0.0,6.8,5.6,0.0,1.0);
glTexCoord2f(1,0); glVertex3f(7.2,5.0,-1.35);//-1.25);
glTexCoord2f(0,0); glVertex3f(6.8,5.0,0.0);
glTexCoord2f(0,1); glVertex3f(6.8,5.6,0.0);
glTexCoord2f(1,1); glVertex3f(7.2,5.6,-1.35);

glEnd();
glDisable(GL_TEXTURE_2D);


glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, h);
glBegin(GL_QUADS);
//draw right sign
calculateNormal2(6.8,5.0,0.0,3.5,5.0,1.2,3.5,5.6,1.2,1.0);
glTexCoord2f(1,0); glVertex3f(6.8,5.0,0.0);
glTexCoord2f(0,0); glVertex3f(3.5,5.0,1.2);
glTexCoord2f(0,1); glVertex3f(3.5,5.6,1.2);
glTexCoord2f(1,1); glVertex3f(6.8,5.6,0.0);

glBindTexture(GL_TEXTURE_2D, h);
//draw left sign
calculateNormal2(7.2,5.0,-1.35,5.0,5.0,-3.9,5.0,5.6,-3.9,-1.0);
glTexCoord2f(0,0); glVertex3f(7.2,5.0,-1.35);
glTexCoord2f(1,0); glVertex3f(5,5.0,-3.9);
glTexCoord2f(1,1); glVertex3f(5,5.6,-3.9);
glTexCoord2f(0,1); glVertex3f(7.2,5.6,-1.35);


glEnd();
glDisable(GL_TEXTURE_2D);

glBegin(GL_TRIANGLES);

//draw right triangle for sign
calculateNormal2(3.5,5.0,1.2,3.5,5.6,1.2,3.2,5.0,1.3,-1.0);
glVertex3f(3.5,5.0,1.2);
glVertex3f(3.5,5.6,1.2);
glVertex3f(3.2,5.0,1.3);

//draw left triangle for sign
calculateNormal2(5.0,5.0,-3.9,5.0,5.6,-3.9,4.7,5.0,-4.25,1.0);
glVertex3f(5,5.0,-3.9);
glVertex3f(5,5.6,-3.9);
glVertex3f(4.7,5.0,-4.25);

//draw top tirangle for sign
calculateNormal2(6.8,5.6,0.0,7.2,5.6,-1.35,7.0,5.78,-.675,-1.0);
glVertex3f(6.8,5.6,0.0);
glVertex3f(7.2,5.6,-1.35);
glVertex3f(7.0,5.78,-.675);

glEnd();

glPopMatrix();
}

static void saloon1(double sx, double sy, double sz, double theta, double tx, double ty, double tz){

glPushMatrix();


glTranslated(tx,ty,tz);
glScaled(sx,sy,sz);
glRotated(theta,0,1,0);

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, wood4);

glBegin(GL_QUADS);

//glColor3f(0.9,0.0,0.0);
//draw front
calculateNormal2(0,0,0,5,0,0,5,6,0,1);
glTexCoord2f(0,0); glVertex3f(0,0,0);
glTexCoord2f(1,0); glVertex3f(5,0,0);
glTexCoord2f(1,1); glVertex3f(5,6,0);
glTexCoord2f(0,1); glVertex3f(0,6,0);

glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,l);

glBegin(GL_QUADS);

calculateNormal2(0,4,-0.1,5,4,-0.1,5,6,-0.1,1.0);
glTexCoord2f(1,0); glVertex3f(0,4,-0.1);
glTexCoord2f(0,0); glVertex3f(5,4,-0.1);
glTexCoord2f(0,1); glVertex3f(5,6,-0.1);
glTexCoord2f(1,1); glVertex3f(0,6,-0.1);


glEnd();
glDisable(GL_TEXTURE_2D);


glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,wood4);
glBegin(GL_QUADS);

//draw right side
glTexCoord2f(0,0); glVertex3f(0,0,0);
glTexCoord2f(0,1); glVertex3f(0,4.5,0);
glTexCoord2f(1,1); glVertex3f(0,4.5,7);
glTexCoord2f(1,0); glVertex3f(0,0,7);

//draw left side
glTexCoord2f(0,0); glVertex3f(5,0,0);
glTexCoord2f(0,1); glVertex3f(5,4.5,0);
glTexCoord2f(1,1); glVertex3f(5,4.5,7);
glTexCoord2f(1,0); glVertex3f(5,0,7);

//draw back
glTexCoord2f(0,0); glVertex3f(0,0,7);
glTexCoord2f(1,0); glVertex3f(5,0,7);
glTexCoord2f(1,1); glVertex3f(5,4.5,7);
glTexCoord2f(0,1); glVertex3f(0,4.5,7);
glEnd();
glDisable(GL_TEXTURE_2D);

glBegin(GL_QUADS);
glColor3f(1,1,1);
//draw roof
glVertex3f(0,4.5,0);
glVertex3f(5,4.5,0);
glVertex3f(5,4.5,7);
glVertex3f(0,4.5,7);

glColor3f(0.5,0.5,0.5);
//draw balcony
glVertex3f(0,3,0);
glVertex3f(5,3,0);
glVertex3f(5,3,-2);
glVertex3f(0,3,-2);

glEnd();

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,wood4);
glBegin(GL_QUADS);
//draw right balcony railing
double i;
for (i = -2.0; i < 0.0; i+=0.25)
{
glTexCoord2f(0,0); glVertex3f(5,3,i);
glTexCoord2f(1,0); glVertex3f(5,3,i+0.15);
glTexCoord2f(1,1); glVertex3f(5,3.5,i+0.15);
glTexCoord2f(0,1); glVertex3f(5,3.5,i);
}

glColor3f(0.4,0.4,0.4);
//draw front balconay railing
for (i = 5.0; i > 0.0; i-=0.25)
{
glTexCoord2f(0,0); glVertex3f(i,3,-2);
glTexCoord2f(1,0); glVertex3f(i-0.15,3,-2);
glTexCoord2f(1,1); glVertex3f(i-0.15,3.5,-2);
glTexCoord2f(0,1); glVertex3f(i,3.5,-2);
}

//draw left balcony railing
for (i = -2.0; i < 0.0; i+=0.25)
{
glTexCoord2f(0,0); glVertex3f(0,3,i);
glTexCoord2f(1,0); glVertex3f(0,3,i+0.15);
glTexCoord2f(1,1); glVertex3f(0,3.5,i+0.15);
glTexCoord2f(0,1); glVertex3f(0,3.5,i);
}



glEnd();
glDisable(GL_TEXTURE_2D);
glPopMatrix();
}


static void store1(double sx, double sy, double sz, double theta, double tx, double ty, double tz){

count +=1;
glPushMatrix();
glTranslated(tx,ty,tz);
glScaled(sx,sy,sz);
glRotated(theta,0,1,0);

glEnable(GL_TEXTURE_2D);

double height1=5;
if (count%2==0){
//glBindTexture(GL_TEXTURE_2D,face4);


glBindTexture(GL_TEXTURE_2D,face2);



glBegin(GL_QUADS);
double height1=5;


//draw front
calculateNormal2(0,0,0,4,0,0,4,height1-.25,0,1.0);
glTexCoord2f(1,0); glVertex3f(0,0,0);
glTexCoord2f(0,0); glVertex3f(4,0,0);
glTexCoord2f(0,1); glVertex3f(4,height1-.25,0);
glTexCoord2f(1,1); glVertex3f(0,height1-.25,0);

glEnd();
glDisable(GL_TEXTURE_2D);
goto here;
}


if (count%3==0){
glBindTexture(GL_TEXTURE_2D,face5);

glBegin(GL_QUADS);
double height1=5;

//draw front
calculateNormal2(0,0,0,4,0,0,4,height1-.25,0,1.0);
glTexCoord2f(1,0); glVertex3f(0,0,0);
glTexCoord2f(0,0); glVertex3f(4,0,0);
glTexCoord2f(0,1); glVertex3f(4,height1-.25,0);
glTexCoord2f(1,1); glVertex3f(0,height1-.25,0);

glEnd();
glDisable(GL_TEXTURE_2D);

goto here;
}

if (count%3==1){
glBindTexture(GL_TEXTURE_2D,face7);

glBegin(GL_QUADS);
double height1=5;

//draw front
calculateNormal2(0,0,0,4,0,0,4,height1-.25,0,1.0);
glTexCoord2f(1,0); glVertex3f(0,0,0);
glTexCoord2f(0,0); glVertex3f(4,0,0);
glTexCoord2f(0,1); glVertex3f(4,height1-.25,0);
glTexCoord2f(1,1); glVertex3f(0,height1-.25,0);

glEnd();
glDisable(GL_TEXTURE_2D);

goto here;
}




else {
glBindTexture(GL_TEXTURE_2D,face3);

glBegin(GL_QUADS);
double height1=5;

//draw front
calculateNormal2(0,0,0,4,0,0,4,height1-.25,0,1.0);
glTexCoord2f(1,0); glVertex3f(0,0,0);
glTexCoord2f(0,0); glVertex3f(4,0,0);
glTexCoord2f(0,1); glVertex3f(4,height1-.25,0);
glTexCoord2f(1,1); glVertex3f(0,height1-.25,0);

glEnd();
glDisable(GL_TEXTURE_2D);


}

here:
//draw advertisement
if (count%2==0){
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,sign1);
glBegin(GL_QUADS);

calculateNormal2(4.01,0,6,4.01,0,0,4.01,4,0,-1);
glTexCoord2f(0,0); glVertex3f(4.01,0,6);
glTexCoord2f(1,0); glVertex3f(4.01,0,0);
glTexCoord2f(1,1); glVertex3f(4.01,4,0);
glTexCoord2f(0,1); glVertex3f(4.01,4,6);

glEnd();
glDisable(GL_TEXTURE_2D);
}

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,wood5);
glBegin(GL_QUADS);

//now draw the sides
double numOfSides;

double dz = 0;

for (numOfSides=1.0; numOfSides<6.0; numOfSides+=1.0){

//draw left side
calculateNormal2(0,0,dz,0,height1-(.25*numOfSides),dz,0,height1-(.25*numOfSides),dz+2,1.0);
glTexCoord2f(0,0); glVertex3f(0,0,dz);
glTexCoord2f(0,1); glVertex3f(0,height1-(.25*numOfSides),dz);
glTexCoord2f(1,1); glVertex3f(0,height1-(.25*numOfSides),dz+2);
glTexCoord2f(1,0); glVertex3f(0,0,dz+2);

//draw right side
calculateNormal2(4,0,dz,4,height1-(.25*numOfSides),dz,4,height1-(.25*numOfSides),dz+2,-1.0);
glTexCoord2f(0,0); glVertex3f(4,0,dz);
glTexCoord2f(0,1); glVertex3f(4,height1-(.25*numOfSides),dz);
glTexCoord2f(1,1);  glVertex3f(4,height1-(.25*numOfSides),dz+2);
glTexCoord2f(1,0); glVertex3f(4,0,dz+2);



//now draw these a roof
calculateNormal2(0,height1-(.25*numOfSides),dz,4,height1-(.25*numOfSides),dz,4,height1-(.25*numOfSides),dz+2,1.0);
glVertex3f(0,height1-(.25*numOfSides),dz);
glVertex3f(4,height1-(.25*numOfSides),dz);
glVertex3f(4,height1-(.25*numOfSides),dz+2);
glVertex3f(0,height1-(.25*numOfSides),dz+2);


if (numOfSides != 5.0){
//now for some bondo at the top back
calculateNormal2(4.0,height1-(.25*numOfSides),dz+2,0,height1-(.25*numOfSides),dz+2,0,height1-(.5*numOfSides),dz+2,-1.0);
glVertex3f(4,height1-(.25*numOfSides),dz+2);
glVertex3f(0,height1-(.25*numOfSides),dz+2);
glVertex3f(0,height1-(.5*numOfSides),dz+2);
glVertex3f(4,height1-(.5*numOfSides),dz+2);
}

dz+=2;
}

//draw back
calculateNormal2(0,0,10,4,0,10,4,3.75,10,-1.0);
glTexCoord2f(0,0); glVertex3f(0,0,10);
glTexCoord2f(1,0); glVertex3f(4,0,10);
glTexCoord2f(1,1); glVertex3f(4,3.75,10);
glTexCoord2f(0,1); glVertex3f(0,3.75,10);


glEnd();
glDisable(GL_TEXTURE_2D);
glPopMatrix();
}



static void birdCage(double sx, double sy, double sz, double theta, double tx, double ty, double tz)
{


glPushMatrix();

glTranslated(tx,ty,tz);
glScaled(sx,sy,sz);
glRotated(theta,0,1,0);

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, d);

glBegin(GL_QUADS);

glColor3f(1.0,0.8431,0.7725);


//draw front
calculateNormal2(0,0,-0.03,4,0,-0.03,4,3.5,-0.03,1.0);
glTexCoord2f(1,0); glVertex3f(0,0,-0.03);
glTexCoord2f(0,0); glVertex3f(4,0,-0.03);
glTexCoord2f(0,1); glVertex3f(4,3.5,-0.03);
glTexCoord2f(1,1); glVertex3f(0,3.5,-0.03);

glEnd();
glDisable(GL_TEXTURE_2D);

if (mman){
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, merman);

glBegin(GL_QUADS);
calculateNormal2(-2,0,-7,-2,0,-0.5,-2,3.5,-0.5,1.0);
glTexCoord2f(1,0); glVertex3f(-2,0,-7);
glTexCoord2f(0,0); glVertex3f(-2,0,-0.5);
glTexCoord2f(0,1); glVertex3f(-2,3.5,-0.5);
glTexCoord2f(1,1); glVertex3f(-2,3.5,-7);

glEnd();
glDisable(GL_TEXTURE_2D);
}

glBegin(GL_QUADS);

//glColor3f(1.0,0.8431,0.7725);

calculateNormal2(0,0,0,4,0,0,4,3.5,0,1.0);
glVertex3f(0,0,0);
glVertex3f(4,0,0);
glVertex3f(4,3.5,0);
glVertex3f(0,3.5,0);


//now draw right side
calculateNormal2(0,0,0,0,0,7,0,3.25,7,1.0);
glVertex3f(0,0,0);
glVertex3f(0,0,7);
glVertex3f(0,3.25,7);
glVertex3f(0,3.25,0);

//now for the left
calculateNormal2(4,0,0,4,0,7,4,3.25,7,-1.0);
glVertex3f(4,0,0);
glVertex3f(4,0,7);
glVertex3f(4,3.25,7);
glVertex3f(4,3.25,0);

//the back
calculateNormal2(4,0,7,0,0,7,0,3.25,7,1.0);
glVertex3f(4,0,7);
glVertex3f(0,0,7);
glVertex3f(0,3.25,7);
glVertex3f(4,3.25,7);

//and then the roof
calculateNormal2(4,3.25,7,0,3.25,7,0,3.25,0,1.0);
glVertex3f(4,3.25,7);
glVertex3f(0,3.25,7);
glVertex3f(0,3.25,0);
glVertex3f(4,3.25,0);



glEnd();
glPopMatrix();



}

static void smallHouse2(double sx, double sy, double sz, double theta, double tx, double ty, double tz){

glPushMatrix();

//printf("glTranslated(%f, %f, %f);", tx,ty,tz);
glTranslated(tx,ty,tz);
glScaled(sx,sy,sz);
glRotated(theta,0,1,0);

glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, k);

glBegin(GL_QUADS);
glColor3f(0.4,0.4,0.4);
calculateNormal2(0.0,3.0,0.01,0.0,4.0,0.01,3.0,3.0,0.01,1.0);
glTexCoord2f(0,0); glVertex3f(0,3,0.01);
glTexCoord2f(1,0); glVertex3f(3,3,0.01);
glTexCoord2f(1,1); glVertex3f(3,4,0.01);
glTexCoord2f(0,1); glVertex3f(0,4,0.01);

glEnd();
glDisable(GL_TEXTURE_2D);


glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, wood3);
glBegin(GL_QUADS);
//draw front
calculateNormal2(0.0,0.0,0.0,3.0,0.0,0.0,3.0,4.0,0.0,-1.0);
glTexCoord2f(0,0); glVertex3f(0,0,0);
glTexCoord2f(1,0); glVertex3f(3,0,0);
glTexCoord2f(1,1); glVertex3f(3,4,0);
glTexCoord2f(0,1); glVertex3f(0,4,0);


//draw right side
calculateNormal2(0.5,0.0,0.0,0.5,0.0,-4.0,0.5,3.0,-4.0,1.0);
glTexCoord2f(0,0); glVertex3f(0.5,0,0);
glTexCoord2f(1,0); glVertex3f(0.5,0,-4);
glTexCoord2f(1,1); glVertex3f(0.5,3,-4);
glTexCoord2f(0,1); glVertex3f(0.5,3,0);

//draw left side
calculateNormal2(2.5,0.0,0.0,2.5,0.0,-4.0,2.5,3.0,-4.0,-1.0);
glTexCoord2f(0,0); glVertex3f(2.5,0,0);
glTexCoord2f(1,0); glVertex3f(2.5,0,-4);
glTexCoord2f(1,1); glVertex3f(2.5,3,-4);
glTexCoord2f(0,1); glVertex3f(2.5,3,0);

//draw back
calculateNormal2(0.5,0.0,-4.0,2.5,0.0,-4.0,2.5,3.0,-4.0,1.0);
glTexCoord2f(0,0); glVertex3f(0.5,0,-4);
glTexCoord2f(1,0); glVertex3f(2.5,0,-4);
glTexCoord2f(1,1); glVertex3f(2.5,3,-4);
glTexCoord2f(0,1); glVertex3f(0.5,3,-4);

//draw roof
calculateNormal2(2.5,3.0,0.0,0.5,3.0,0.0,0.5,3.0,-4.0,1.0);
glVertex3f(2.5,3,0);
glVertex3f(0.5,3,0);
glVertex3f(0.5,3,-4);
glVertex3f(2.5,3,-4);

//draw canopy
calculateNormal2(0.0,3.0,0.0,3.0,3.0,0.0,3.0,2.4,1.0,1.0);
glVertex3f(0,3,0);
glVertex3f(3,3,0);
glVertex3f(3,2.4,1);
glVertex3f(0,2.4,1);



glEnd();
glDisable(GL_TEXTURE_2D);

glPopMatrix();


}



static void drawWorld(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
  /*Note
*I calculated all of the normals using the cross product of the vertex vectors
*/

// This functions renders the pyramid and the tent



   //  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   //glPushMatrix();
   //  Offset, scale and rotate
   //glTranslated(x,y,z);
   //glRotated(th,0,1,0);
   //glScaled(dx,dy,dz); 
   DEM();
   drawRoads();
   //saloon(0.0,0.0,0.0,0.0,0.0,0.0,0.0);
   
   //birdCage(1.0,1.0,1.0,5.0,5.0,5.0,0.0);
   //occidentalHotel(1.0,1.0,1.0,0.0,0.0,0.0,0.0);
   //church(0.0,0.0,0.0,0.0,0.0,0.0,0.0);
   //store(0.0,0.0,0.0,0.0,0.0,0.0,0.0);
   //birdCage(1.0,1.0,1.0,5.0,5.0,5.0,0.0);
   //drawBuildings();
   skyBox(200);
   //texture();
    

   //glPopMatrix();
}

static void skyBox(double D)
{
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);

    double D1 = D - (D/2);
    double D12 = D + (D/2);
 
   //  Sides
   glBindTexture(GL_TEXTURE_2D,b);
   glBegin(GL_QUADS);
   glTexCoord2f(0.00,0); glVertex3f(-D,-D1,-D);
   glTexCoord2f(0.25,0); glVertex3f(+D,-D1,-D);
   glTexCoord2f(0.25,1); glVertex3f(+D,+D12,-D);
   glTexCoord2f(0.00,1); glVertex3f(-D,+D12,-D);

   glTexCoord2f(0.25,0); glVertex3f(+D,-D1,-D);
   glTexCoord2f(0.50,0); glVertex3f(+D,-D1,+D);
   glTexCoord2f(0.50,1); glVertex3f(+D,+D12,+D);
   glTexCoord2f(0.25,1); glVertex3f(+D,+D12,-D);

   glTexCoord2f(0.50,0); glVertex3f(+D,-D1,+D);
   glTexCoord2f(0.75,0); glVertex3f(-D,-D1,+D);
   glTexCoord2f(0.75,1); glVertex3f(-D,+D12,+D);
   glTexCoord2f(0.50,1); glVertex3f(+D,+D12,+D);

   glTexCoord2f(0.75,0); glVertex3f(-D,-D1,+D);
   glTexCoord2f(1.00,0); glVertex3f(-D,-D1,-D);
   glTexCoord2f(1.00,1); glVertex3f(-D,+D12,-D);
   glTexCoord2f(0.75,1); glVertex3f(-D,+D12,+D);
   glEnd();

   //  Top and bottom
   /*glBindTexture(GL_TEXTURE_2D,sky[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0,0); glVertex3f(+D,+D,-D);
   glTexCoord2f(0.5,0); glVertex3f(+D,+D,+D);
   glTexCoord2f(0.5,1); glVertex3f(-D,+D,+D);
   glTexCoord2f(0.0,1); glVertex3f(-D,+D,-D);

   glTexCoord2f(1.0,1); glVertex3f(-D,-D,+D);
   glTexCoord2f(0.5,1); glVertex3f(+D,-D,+D);
   glTexCoord2f(0.5,0); glVertex3f(+D,-D,-D);
   glTexCoord2f(1.0,0); glVertex3f(-D,-D,-D);
   glEnd();*/

   glDisable(GL_TEXTURE_2D);
}

static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

static void ball(double x,double y,double z,double r)
{
   int theta,phi;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glPushMatrix();
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   for (phi=-90;phi<90;phi+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (theta=0;theta<=360;theta+=2*inc)
      {
         Vertex(theta,phi);
         Vertex(theta,phi+inc);
      }
      glEnd();
   }
   glPopMatrix();
}

void Project(double fov,double asp,double dim)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (fov)
      gluPerspective(fov,asp,dim/16,16*dim);
   else
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-dim,+dim);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
/*
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}
*/
void display()
{
   const double len=2.0;  
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);



   glLoadIdentity();
//glTranslated(upDown,leftRight,0);

 
  
   
   
     
      //printf("translating by %d, 0, %d\n",upDown, leftRight);
      //glTranslated(upDown,0,leftRight);
     //tsr 

     glRotatef(ph,1,0,0);

     glRotatef(th,0,1,0);
   
    
    if (!mode1)
      //first person navigation
      glTranslated(-xxx,height,-zzz);
    else
      //overtop view
      glTranslated(-upDown,height,leftRight);
      //glTranslated(leftRight*Sin(th),height,leftRight*-1*Cos(th));
      
      glScaled(2,2,2);
      //glTranslated(leftRight*Sin(th),height,leftRight*-1*Cos(th));
      //glRotatef(ph,0,1,0);
      
    
      
  

   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   if (light)
   {
	glTranslated(0,10,20);
        float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        float Position[]  = {distance*Cos(zh)+60,ylight,distance*Sin(zh)+35,1.0};
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2], 6);
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
     glDisable(GL_LIGHTING);

  
   drawWorld(+1,0,0 , 0.5,0.5,0.5 , 0);
   

   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();

      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");

      if(displayNames){
      glRasterPos3d(86.0,9.0,30.0);
      Print("Allen Street");
      glRasterPos3d(89.0,9.0,69.0);
      Print("Fremont Street");
      glRasterPos3d(33.0,7.0,50.0);
      Print("6th Street");
      glRasterPos3d(69.0,7.0,50.0);
      Print("5th Street");
      glRasterPos3d(105.0,7.0,50.0);
      Print("4th Street");
      glRasterPos3d(141.0,7.0,50.0); 
      Print("3rd Street");

      }
 
   }



   glFlush();
   glutSwapBuffers();

}


void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   glutPostRedisplay();
}

void special(int key,int x,int y)
{
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   else if (key == GLUT_KEY_UP)
      ph += 5;
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.5;
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.5;
   th %= 360;
   ph %= 360;
   Project(mode?fov:0,asp,dim);
   glutPostRedisplay();
}

void key(unsigned char ch,int x,int y)
{
   if (ch == 27)
      exit(0);
   else if (ch == '0')
      th = ph = 0;
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   else if (ch == 'p' || ch == 'P')
      mode1 = 1-mode1;
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   else if (ch == 'd')
      upDown += 5;
   else if (ch == 'n')
      displayNames = 1-displayNames;
   else if (ch == 'a')
      upDown -= 5;
   else if (ch == 's'){
      if (mode1)
        leftRight += 5;
      else{
        xxx -= Sin(th) ;
        zzz += Cos(th) ;}
}

   else if (ch == 'w'){
      if (mode1)
      leftRight -= 5;
      else{
      xxx += Sin(th) ;
      zzz -= Cos(th) ;}
          }

   else if (ch == 'q')
      height += 5;
   else if (ch == 'e')
      height -= 5;
   else if (ch == '.')
      zh += 2;
   else if (ch == ',')
      zh -= 2;
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   else if (ch=='[')
      ylight -= 5;
   else if (ch==']')
      ylight += 5;
   else if (ch=='1')
      mman = 1-mman;
  
     
   Project(mode?fov:0,asp,dim);
   glutIdleFunc(move?idle:NULL);
   glutPostRedisplay();


}

void reshape(int width,int height)
{
   asp = (height>0) ? (double)width/height : 1;
   
   glViewport(0,0, width,height);

   Project(mode?fov:0,asp,dim);
}



int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(700,700);
   glutCreateWindow("HW6");
   
   glutDisplayFunc(display);
 
   glutReshapeFunc(reshape);

   glutSpecialFunc(special);
  
   glutKeyboardFunc(key);
     
   glutIdleFunc(idle);
  
   //load in my three textures
   
   a = LoadTexBMP(groundTexture);
   b = LoadTexBMP(sky);
   d = LoadTexBMP(bc);
   wood1 = LoadTexBMP("wood1.bmp");
   f = LoadTexBMP("hotel.bmp");
   g = LoadTexBMP("window1.bmp");
   h = LoadTexBMP("OCCIDENTALSIGN.bmp");
   i = LoadTexBMP("americanFlag.bmp");
   j = LoadTexBMP("wood2.bmp");
   k = LoadTexBMP("guns.bmp");
   l = LoadTexBMP("saloonSign.bmp");
   wood2 = LoadTexBMP("wood2.bmp");
   wood3 = LoadTexBMP("wood3.bmp");
   wood4 = LoadTexBMP("wood4.bmp");
   wood5 = LoadTexBMP("wood5.bmp");
   face1 = LoadTexBMP("face1.bmp");
   face2 = LoadTexBMP("face2.bmp");
   face3 = LoadTexBMP("face3.bmp");
   face4 = LoadTexBMP("face4.bmp");
   face5 = LoadTexBMP("face5.bmp");
   face6 = LoadTexBMP("face6.bmp");
   face7 = LoadTexBMP("face7.bmp");
   sign1 = LoadTexBMP("sign1.bmp");
   door1 = LoadTexBMP("door1.bmp");
   door2 = LoadTexBMP("door2.bmp");
   merman = LoadTexBMP("merman.bmp");
   glutMainLoop();
   return 0;
}
