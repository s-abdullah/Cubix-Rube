///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// cubix rube.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

// #include "stl.h"

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include "vector"

// Function Prototypes ////////////////////////////////////

void drawAxes();
void cleanup();
void camera();
void DrawTexed();
void makearray();
void checkrotation(int rot, int value);
void drawcube( float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3, float d1, float d2, float d3, float e1, float e2, float e3, float f1, float f2, float f3);
void drawcube1(int value, float a1, float a2,  float b1, float b2,  float c1, float c2,  float d1, float d2,  float e1, float e2,  float f1, float f2);


float poop1,poop2,poop3,poop4,poop5,poop6;
float nice0,nice1,nice2,nice3,nice4,nice5,nice6,nice7,nice10,nice11,nice12,nice13,nice14,nice15,nice16,nice17;

int randomizer = 0;

float cam_xrot = 20; 
float cam_yrot = 45; 
float cam_zrot = 0;

char keyPressed = 'A';

int theta = 0;
int phi = 0;
int beta = 0;
int gamma = 0;
int phi1 = 0;
int beta1 = 0;
int gamma1 = 0;

int reset = 90;
int reseter = 0;

float divisions = 4.0;
float off = 1/divisions;
float offC = 0.25;

int checker = 255;

// variables for changing texture coordinates
float changerGG = 0.0;
float changerBB = 0.0;
float changerPP = 0.0;
float changerGg = 0.0;
float changerBb = 0.0;
float changerPp = 0.0;
float eChange = 0.0;

int counterP = 0;
int counterG = 0;
int counterB = 0;

//variables for texture mapping
float greenY = 0.0;
float greenX = 0.25;

float blueY = 0.0;
float blueX = 0.75;

float redY = 0.25;
float redX = 0.0;

float blackY = 0.25;
float blackX = 0.75;

float  yellowY = 0.0;
float yellowX = 0.5;

float pinkY = 0.75;
float pinkX = 0.0;

float whiteY = 0.0;
float whiteX = 0.0;

//variable for checking conditions of texture jumps
int rotation = 0;
int prevRot = 0;
int cubeNo = 0;
int jump = -1;
int counter = 0;
std::vector<float> v1;
std::vector<float> v2;
std::vector<float> v3;
std::vector<float> v4;
std::vector<float> v5;
std::vector<float> v6;

// globals for texture image creaation
#define TexImageWidth 64
#define TexImageHeight 64

static GLubyte TexImage[TexImageHeight][TexImageWidth][4];
static GLuint texName;

// 3D array ti keep track of cubes
int forL = 1;
int forl = 2;
int myarray[3][3][3];



GLUquadric* qobj;
void vectorReset(){
	v1.clear();
	v2.clear();
	v3.clear();
	v4.clear();
	v5.clear();
	v6.clear();
}


void vectorinit(){




	for (int i = 0; i < 9; ++i)
	{
		v1.push_back(greenY);
		v1.push_back(greenX);
		v2.push_back(pinkY);
		v2.push_back(pinkX);
		v3.push_back(blueY);
		v3.push_back(blueX);
		v4.push_back(redY);
		v4.push_back(redX);
		v5.push_back(whiteY);
		v5.push_back(whiteX);
		v6.push_back(yellowY);
		v6.push_back(yellowX);
	}
}


void initLight(void)
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.8, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

}







void makeTexImage(void)
{
	int i, j, c1, c2, c3;

	for (i = 0; i < TexImageHeight; i++) {
		for (j = 0; j < TexImageWidth; j++) {
			if(j < (TexImageHeight/divisions)){
					if((i < (TexImageHeight/divisions)))
					{
						if((j <= 0)||(j >= ((TexImageHeight/divisions) - 1))||(i <= 0)||(i >= ((TexImageHeight/divisions) - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{	
							c1 = 255;
							c2 = 255;
							c3 = 255;
						}
					}
					else if((i < ((TexImageHeight/divisions)*2)))
					{
						if((j <= 0)||(j >= ((TexImageHeight/divisions) - 1))||(i <= (TexImageHeight/divisions))||(i >= ((TexImageHeight/divisions)*2 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 0;
							c2 = 255;
							c3 = 0;
						}
					}
					else if((i < ((TexImageHeight/divisions)*3)))
					{
						if((j <= 0)||(j >= ((TexImageHeight/divisions) - 1))||(i <= ((TexImageHeight/divisions)*2))||(i >= ((TexImageHeight/divisions)*3 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 255;
							c2 = 255;
							c3 = 0;
						}
					}
					else
					{
						if((j <= 0)||(j >= ((TexImageHeight/divisions) - 1))||(i <= ((TexImageHeight/divisions)*3))||(i >= ((TexImageHeight/divisions)*4 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 0;
							c2 = 0;
							c3 = 255;
						}
					}
			}
			else if(j < ((TexImageHeight/divisions)*2))
			{
					if((i < (TexImageHeight/divisions)))
					{
						if((j <= (TexImageHeight/divisions))||(j >= ((TexImageHeight/divisions)*2 - 1))||(i <= 0)||(i >= ((TexImageHeight/divisions) - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 255;
							c2 = 0;
							c3 = 0;
						}
					}
					else if((i < ((TexImageHeight/divisions)*2)))
					{
						if((j <= (TexImageHeight/divisions))||(j >= ((TexImageHeight/divisions)*2 - 1))||(i <= (TexImageHeight/divisions))||(i >= ((TexImageHeight/divisions)*2 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 0;
							c2 = 0;
							c3 = 255;
					}
					}
					else if((i < ((TexImageHeight/divisions)*3)))
					{
						if((j <= (TexImageHeight/divisions))||(j >= ((TexImageHeight/divisions)*2 - 1))||(i <= ((TexImageHeight/divisions)*2))||(i >= ((TexImageHeight/divisions)*3 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 255;
							c2 = 0;
							c3 = 255;
						}
					}
					else
					{
						if((j <= (TexImageHeight/divisions))||(j >= ((TexImageHeight/divisions)*2 - 1))||(i <= ((TexImageHeight/divisions)*3))||(i >= ((TexImageHeight/divisions)*4 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
					}
			}
			else if(j < ((TexImageHeight/divisions)*3))
			{
					if((i < (TexImageHeight/divisions)))
					{
						if((j <= ((TexImageHeight/divisions)*2))||(j >= ((TexImageHeight/divisions)*3 - 1))||(i <= 0)||(i >= ((TexImageHeight/divisions) - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{	
							c1 = 255;
							c2 = 255;
							c3 = 0;
						}
					}
					else if((i < ((TexImageHeight/divisions)*2)))
					{
						if((j <= ((TexImageHeight/divisions)*2))||(j >= ((TexImageHeight/divisions)*3 - 1))||(i <= (TexImageHeight/divisions))||(i >= ((TexImageHeight/divisions)*2 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 0;
							c2 = 0;
							c3 = 255;
						}
					}
					else if((i < ((TexImageHeight/divisions)*3)))
					{
						if((j <= ((TexImageHeight/divisions)*2))||(j >= ((TexImageHeight/divisions)*3 - 1))||(i <= ((TexImageHeight/divisions)*2))||(i >= ((TexImageHeight/divisions)*3 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 255;
							c2 = 255;
							c3 = 255;
						}
					}
					else
					{
						if((j <= ((TexImageHeight/divisions)*2))||(j >= ((TexImageHeight/divisions)*3 - 1))||(i <= ((TexImageHeight/divisions)*3))||(i >= ((TexImageHeight/divisions)*4 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else
						{
							c1 = 0;
							c2 = 255;
							c3 = 0;
						}
					}
			}
			else
			{
				if((i < (TexImageHeight/divisions)))
					{
						if((j <= ((TexImageHeight/divisions)*3))||(j >= ((TexImageHeight/divisions)*4 - 1))||(i <= 0)||(i >= ((TexImageHeight/divisions) - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 255;
							c2 = 0;
							c3 = 255;
						}
					}
					else if((i < ((TexImageHeight/divisions)*2)))
					{
						if((j <= ((TexImageHeight/divisions)*3))||(j >= ((TexImageHeight/divisions)*4 - 1))||(i <= (TexImageHeight/divisions))||(i >= ((TexImageHeight/divisions)*2 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 0;
							c2 = 255;
							c3 = 0;
					}
					}
					else if((i < ((TexImageHeight/divisions)*3)))
					{
						if((j <= ((TexImageHeight/divisions)*3))||(j >= ((TexImageHeight/divisions)*4 - 1))||(i <= ((TexImageHeight/divisions)*2))||(i >= ((TexImageHeight/divisions)*3 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 255;
							c2 = 0;
							c3 = 0;
						}
					}
					else
					{
						if((j <= ((TexImageHeight/divisions)*3))||(j >= ((TexImageHeight/divisions)*4 - 1))||(i <= ((TexImageHeight/divisions)*3))||(i >= ((TexImageHeight/divisions)*4 - 1))){
							c1 = 0;
							c2 = 0;
							c3 = 0;
						}
						else{
							c1 = 0;
							c2 = 0;
							c3 = 255;
						}
					}
			}
					TexImage[i][j][0] = (GLubyte)c1;
					TexImage[i][j][1] = (GLubyte)c2;
					TexImage[i][j][2] = (GLubyte)c3;
					TexImage[i][j][3] = (GLubyte)255; 
		}
	}
}




void DrawTexed()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	// camera();
	float aaa = 0.0;
	float bbb = 1.0;
	float TexIm = 4.5;
	glBegin(GL_QUADS);

		

		glTexCoord2f(aaa, aaa);
				glVertex3f(-TexIm, TexIm, TexIm);

		glTexCoord2f(aaa, bbb);
				glVertex3f(TexIm, TexIm, TexIm);

		glTexCoord2f(bbb, bbb);
				glVertex3f(TexIm, TexIm, -TexIm);

		glTexCoord2f(bbb,aaa);


		glVertex3f(-TexIm, TexIm, -TexIm);


		// glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
		// glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
		// glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
		// glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
	glEnd();
	glFlush();

	glDisable(GL_TEXTURE_2D);
}



void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/////////////////////////////////
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	makeTexImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexImageWidth,TexImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,TexImage);//binding texture
	/////////////////////////////////
	initLight();
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
}

///////////////////////////////////////////////////////////
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera();
	makearray();
	drawAxes();
	// glPushMatrix();
	// 	glRotatef(-45,0,1,0);
	// 	glRotatef(90,1,0,0);
	// 	// glTranslatef(-30,-45,0);
	// 	DrawTexed();
	// glPopMatrix();



////////////////////////////////////////////////////////////////////////////
	///condition for switiching position og green texture coorditante
// if ((prevRot != 0)&&((prevRot) != (rotation)))
// {
// 	float remain;
// 	remain = (eChange/offC)*90;
// 	if((abs(prevRot) == 2)){
// 				// glRotatef((gamma*counterG), 1, 0, 0);//face
// 		// glRotatef(beta, 1, 0, 0);//side
// 				// glRotatef((phi*counterP), 1, 0, 0);//side
// 		if (prevRot == 2)
// 		{
// 			jump = 1;
// 			changerBB = eChange;
// 			eChange = 0;
// 			beta -= remain;

// 		}
// 		else if (prevRot == -2)
// 		{
// 			jump = 1;
// 			changerBB = eChange;
// 			eChange = 0;
// 			beta += remain;
// 		}
				
				
// 	}
// 	if((abs(prevRot) == 3)){
// 				// glRotatef((gamma*counterG), 0, 1, 0);//face
// 				// glRotatef((beta*counterB), 0, 1, 0);//side			
// 		// glRotatef(phi, 0, 1, 0);//side
// 		if (prevRot == 3)
// 		{
// 			jump = 2;
// 			changerPP = eChange;
// 			eChange = 0;
// 			phi -= remain;
// 		}
// 		else if (prevRot == -3)
// 		{
// 			jump = 2;
// 			changerPP = eChange;
// 			eChange = 0;
// 			phi += remain;
// 		}
				
// 	}
// 	if((abs(prevRot) == 1)){
// 		// glRotatef(gamma, 0, 0, 1);//face
// 				// glRotatef((beta*counterB), 0, 0, 1);//side
// 				// glRotatef((phi*counterP), 0, 0, 1);//side	
// 		if (prevRot == 1)
// 		{
// 			jump = 0;
// 			changerGG = eChange;
// 			eChange = 0;
// 			gamma -= remain;
// 		}
// 		else if (prevRot == -1)
// 		{
// 			jump = 0;
// 			changerGG = eChange;
// 			eChange = 0;
// 			gamma += remain;
// 		}	
// 	}
	
// 	if((abs(prevRot) == 5)){
// 		// glRotatef(beta1, 1, 0, 0);//side
// 				// glRotatef((phi1*counterP), 1, 0, 0);//side
// 				// glRotatef((gamma1*counterG), 1, 0, 0);//face
// 		if (prevRot == 5)
// 		{
// 			jump = 1;
// 			changerBb = eChange;
// 			eChange = 0;
// 			beta1 -= remain;
// 		}
// 		else if (prevRot == -5)
// 		{
// 			jump = 1;
// 			changerBb = eChange;
// 			eChange = 0;
// 			beta += remain;
// 		}

// 	}
// 	if((abs(prevRot) == 6)){
// 				// glRotatef((beta1*counterB), 0, 1, 0);//side
// 				// glRotatef((gamma1*counterG), 0, 1, 0);//face
// 		// glRotatef(phi1, 0, 1, 0);//side
// 		if (prevRot == 6)
// 		{
// 			jump = 2;
// 			changerPp = eChange;
// 			eChange = 0;
// 			phi1 -= remain;
// 		}
// 		else if (prevRot == -6)
// 		{
// 			jump = 2;
// 			changerPp = eChange;
// 			eChange = 0;
// 			phi1 += remain;
// 		}


// 	}
// 	if((abs(prevRot) == 4)){
// 				// glRotatef((beta1*counterB), 0, 0, 1);//side
// 				// glRotatef((phi1*counterP), 0, 0, 1);//side
// 		// glRotatef(gamma1, 0, 0, 1);//face
// 		if (prevRot == 4)
// 		{
// 			jump = 0;
// 			changerGg = eChange;
// 			eChange = 0;
// 			gamma1 -= remain;
// 		}
// 		else if (prevRot == -4)
// 		{
// 			jump = 0;
// 			changerGg = eChange;
// 			eChange = 0;
// 			gamma1 += remain;
// 		}


// 	}
// }

// ////////////////////////////////////////////////////////////////////

// 	if (jump == 0)
// 	{
// 		greenY = 0.0;

// 		blueY = 0.0;

// 		redY = 0.25;
// 		redX = 0.0;

// 		yellowY = 0.0;
// 		yellowX = 0.5;
// 	}
// 	else if (jump == 1)
// 	{
// 		greenY = 0.75;

// 		blueY = 0.75;

// 		redY = 0.75;
// 		redX = 0.5;

// 		yellowY = 0.5;
// 		yellowX = 0.0;
// 	}
// 	else if (jump == 2)
// 	{
// 		greenY = 0.75;
// 		blueY = 0.75;

// 		redY = 0.25;
// 		redX = 0.0;

// 		yellowY = 0.5;
// 		yellowX = 0.0;
// 	}

///////////////////////////////////////////////////

	//  BACK FACE //
	cubeNo = 0;

	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,25);
		glTranslatef(-9, -9, -9);   // bottom left
		drawcube1(25,blackY,blackX, blackY,blackX, blackY,blackX, (v5[12] + changerPp),(v5[13] + changerGg), (v3[12]),(v3[13] + changerGg + changerBB), (v4[0] + changerPp),(v4[1] + changerBB));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,26);
		glTranslatef(0, -9, -9);    // bottom middle
		drawcube1(26,blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, (v3[14]),(v3[15] + changerGg), (v4[2] + changerPp),(v4[3]));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,27);
		glTranslatef(9, -9, -9);    //bottom right
		drawcube1(27,blackY,blackX, blackY,blackX, (v6[16] + changerPp),(v6[17] + changerGg), blackY,blackX, (v3[16]),(v3[17] + changerGg + changerBb), (v4[4] + changerPp),(v4[5] + changerBb));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,22);
		glTranslatef(-9, 0, -9);    //middle left
		drawcube1(22,blackY,blackX, blackY,blackX, blackY,blackX, (v5[6]),(v5[7] + changerGg), blackY,blackX, v4[6],(v4[7] + changerBB));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,23);
		glTranslatef(0, 0, -9);     //middle middle
		drawcube1(23,blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, v4[8],(v4[9]));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,24);
		glTranslatef(9, 0, -9);		// middle right
		drawcube1(24,blackY,blackX, blackY,blackX, (v6[10]),(v6[11] + changerGg), blackY,blackX, blackY,blackX, v4[10],(v4[11] + changerBb));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,19);
		glTranslatef(-9, 9, -9);		//top left
		drawcube1(19,(v1[0]),(v1[1] + changerGg + changerBB), blackY,blackX, blackY,blackX, (v5[0] + changerPP),(v5[1] + changerGg), blackY,blackX, (v4[12] + changerPP),(v4[13] + changerBB));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,20);
		glTranslatef(0, 9, -9);		//top midddle
		drawcube1(20,(v1[2]),(v1[3] + changerGg), blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, (v4[14] + changerPP),(v4[15]));
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,21);
		glTranslatef(9, 9, -9);		// top right
		drawcube1(21,(v1[4]),(v1[5] + changerGg + changerBb), blackY,blackX, (v6[4] + changerPP),(v6[5] + changerGg), blackY,blackX, blackY,blackX, (v4[16] + changerPP),(v4[17] + changerBb));
	glPopMatrix();











	// FRONT FACE //
	cubeNo = 0;


	glPushMatrix();
		checkrotation(rotation,7);
		glTranslatef(-9, -9, 9);		//bottom left
		drawcube1(7,blackY,blackX, (v2[12] + changerPp),(v2[13] + changerBB), blackY,blackX, (v5[16] + changerPp),(v5[17] + changerGG), (v3[0]),(v3[1] + changerGG + changerBB), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,8);
		glTranslatef(0, -9, 9);		//bottom middle
		drawcube1(8,blackY,blackX, (v2[14] + changerPp),(v2[15]), blackY,blackX, blackY,blackX, (v3[2]),(v3[3] + changerGG), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,9);
		glTranslatef(9, -9, 9);		//bottom right
		drawcube1(9,blackY,blackX, (v2[16] + changerPp),(v2[17] + changerBb), (v6[12] + changerPp),(v6[13] + changerGG), blackY,blackX, (v3[4]),(v3[5] + changerGG + changerBb), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,4);
		glTranslatef(-9, 0, 9);		//middle left
		drawcube1(4,blackY,blackX, v2[6],(v2[7] + changerBB), blackY,blackX, (v5[10]),(v5[11] + changerGG), blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
			checkrotation(rotation,5);
		glTranslatef(0, 0, 9);		//middle middle
		drawcube1(5,blackY,blackX, (v2[8]),(v2[9]), blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();


	glPushMatrix();
		checkrotation(rotation,6);
		glTranslatef(9, 0, 9);		// middle right
		drawcube1(6,blackY,blackX, v2[10],(v2[11] + changerBb), (v6[6]),(v6[7] + changerGG), blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,1);
		glTranslatef(-9, 9, 9);		// top left
		drawcube1(1,(v1[12]),(v1[13] + changerGG + changerBB), (v2[0] + changerPP),(v2[1] + changerBB), blackY,blackX, (v5[4] + changerPP),(v5[5] + changerGG), blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,2);
		glTranslatef(0, 9, 9);		// top middle
		drawcube1(2,(v1[14]),(v1[15] + changerGG), (v2[2] + changerPP),(v2[3]), blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,3);
		glTranslatef(9, 9, 9);		// top right
		drawcube1(3,(v1[16]),(v1[17] + changerGG + changerBb), (v2[4] + changerPP),(v2[5] + changerBb), (v6[0] + changerPP),(v6[1] + changerGG), blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();







	//  MIDDLE FACE  //

	cubeNo = 0;

	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,16);
		glTranslatef(-9, -9, 0);		// bottom left
		drawcube1(16,blackY,blackX, blackY,blackX, blackY,blackX, (v5[14] + changerPp),v5[15], (v3[6]),(v3[7] + changerBB), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,17);
		glTranslatef(0, -9, 0);		// bottom middle
		drawcube1(17,blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, (v3[8]),(v3[9]), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,18);
		glTranslatef(9, -9, 0);		// bottom right
		drawcube1(18,blackY,blackX, blackY,blackX, (v6[14] + changerPp),v6[15], blackY,blackX, (v3[10]),(v3[11] + changerBb), blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,13);
		glTranslatef(-9, 0, 0);		// middle left
		drawcube1(13,blackY,blackX, blackY,blackX, blackY,blackX, (v5[8]),v5[9], blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,14);
		glTranslatef(0, 0, 0);		// middle middle
		drawcube1(14,blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();



	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,15);
		glTranslatef(9, 0, 0);		// middle right
		drawcube1(15,blackY,blackX, blackY,blackX, (v6[8]),v6[9], blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,10);
		glTranslatef(-9, 9, 0);		// top left
		drawcube1(10,(v1[6]),(v1[7] + changerBB), blackY,blackX, blackY,blackX, (v5[2] + changerPP),v5[3], blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,11);
		glTranslatef(0, 9, 0);		// top middle
		drawcube1(11,(v1[8]),(v1[9]), blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();


	cubeNo++;
	glPushMatrix();
		checkrotation(rotation,12);
		glTranslatef(9, 9, 0);		// top right
		drawcube1(12,(v1[10]),(v1[11] + changerBb), blackY,blackX, (v6[2] + changerPP),v6[3], blackY,blackX, blackY,blackX, blackY,blackX);
	glPopMatrix();

	cubeNo = 0;



///////////////////////////////////////////////////



////////////////////////////////////////////////////
	glutSwapBuffers();


}



void makearray() {
	int val = 1;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			for (int k = 0; k<3; k++) {
				myarray[j][k][i] = val;
				val++;
			}
		}
	}
}

void checkrotation(int rot, int value) {
	int xval, yval, zval;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			for (int k = 0; k<3; k++) {
				if (myarray[i][j][k] == value) {
					xval = i;
					yval = j;
					zval = k;
				}
			}
		}
	}

	// conditions for checking possible rotations through 3D array
	if((yval == 0)&&(abs(rot) == 2)){
				glRotatef((gamma*counterG), 1, 0, 0);//face
		glRotatef(beta, 1, 0, 0);//side
				glRotatef((phi*counterP), 1, 0, 0);//side
				
				
	}
	if((xval == 0)&&(abs(rot) == 3)){
				glRotatef((gamma*counterG), 0, 1, 0);//face
				glRotatef((beta*counterB), 0, 1, 0);//side			
		glRotatef(phi, 0, 1, 0);//side
	
				
	}
	if((zval == 0)&&(abs(rot) == 1)){
		glRotatef(gamma, 0, 0, 1);//face
				glRotatef((beta*counterB), 0, 0, 1);//side
				glRotatef((phi*counterP), 0, 0, 1);//side
	
				
	}
	
	if((yval == 2)&&(abs(rot) == 5)){
		glRotatef(beta1, 1, 0, 0);//side
				glRotatef((phi1*counterP), 1, 0, 0);//side
				glRotatef((gamma1*counterG), 1, 0, 0);//face
	}
	if((xval == 2)&&(abs(rot) == 6)){
				glRotatef((beta1*counterB), 0, 1, 0);//side
				glRotatef((gamma1*counterG), 0, 1, 0);//face
		glRotatef(phi1, 0, 1, 0);//side
	}
	if((zval == 2)&&(abs(rot) == 4)){
				glRotatef((beta1*counterB), 0, 0, 1);//side
				glRotatef((phi1*counterP), 0, 0, 1);//side
		glRotatef(gamma1, 0, 0, 1);//face
	}

}


////////////////////////////////
void drawcube1(int value, float a1, float a2,  float b1, float b2,  float c1, float c2,  float d1, float d2,  float e1, float e2,  float f1, float f2) {

//  getting texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	// if(a2 > 0.75){
	// 	a2 = 0.0;
	// }

	// if(b2 > 0.75){
	// 	b2 = 0.0;
	// }

	// if(c2 > 0.75){
	// 	c2 = 0.0;
	// }

	// if(d2 > 0.75){
	// 	d2 = 0.0;
	// }

	// if(e2 > 0.75){
	// 	e2 = 0.0;
	// }

	// if(f2 > 0.75){
	// 	f2 = 0.0;
	// }



	// if(a2 < -0.75){
	// 	a2 = 0.0;
	// }

	// if(b2 < -0.75){
	// 	b2 = 0.0;
	// }

	// if(c2 < -0.75){
	// 	c2 = 0.0;
	// }

	// if(d2 < -0.75){
	// 	d2 = 0.0;
	// }

	// if(e2 < -0.75){
	// 	e2 = 0.0;
	// }

	// if(f2 < -0.75){
	// 	f2 = 0.0;
	// }

// if ((rotation == 3)||(rotation == -3))
// {
// 	if(a2 != 0.0){
// 		a2 = 0.0;
// 	}

// 	if(b2 != 0.0){
// 		b2 = 0.0;
// 	}

// 	if(c2 != 0.0){
// 		c2 = 0.0;
// 	}

// 	if(d2 != 0.0){
// 		d2 = 0.0;
// 	}

// 	if(e2 != 0.0){
// 		e2 = 0.0;
// 	}

// 	if(f2 != 0.0){
// 		f2 = 0.0;
// 	}
// }
// else if ((rotation == 2)||(rotation == -2))
// {
// 	if(a1 != 0.75){
// 		a1 = 0.75;
// 	}

// 	if(b1 != 0.75){
// 		b1 = 0.75;
// 	}

// 	if(c1 != 0.75){
// 		c1 = 0.75;
// 	}

// 	if(d1 != 0.75){
// 		d1 = 0.75;
// 	}

// 	if(e1 != 0.75){
// 		e1 = 0.75;
// 	}

// 	if(f1 != 0.75){
// 		f1 = 0.75;
// 	}
// }
// else if ((rotation == 1)||(rotation == -1))
// {
// 	if(a1 != 0.0){
// 		a1 = 0.0;
// 	}

// 	if(b1 != 0.0){
// 		b1 = 0.0;
// 	}

// 	if(c1 != 0.0){
// 		c1 = 0.0;
// 	}

// 	if(d1 != 0.0){
// 		d1 = 0.0;
// 	}

// 	if(e1 != 0.0){
// 		e1 = 0.0;
// 	}

// 	if(f1 != 0.0){
// 		f1 = 0.0;
// 	}
// }
glPushMatrix();
////////////////////////////////////


//////////////////////////////////
	glBegin(GL_QUADS);
			// top
			//glColor3f(a1, a2, a3);//color of the surface
			glNormal3f(0.0f, 1.0f, 0.0f);// basically tells which axis to the face would be on
			glTexCoord2f(a1, a2);
			glVertex3f(-4.5f, 4.5f, 4.5f);
		
			glTexCoord2f(a1, a2 + off);
			glVertex3f(4.5f, 4.5f, 4.5f);

			glTexCoord2f(a1 + off, a2 + off);
			glVertex3f(4.5f, 4.5f, -4.5f);

			glTexCoord2f(a1 + off, a2);
			glVertex3f(-4.5f, 4.5f, -4.5f);

			// front
			//glColor3f(b1, b2, b3);//color of the surface
			glNormal3f(0.0f, 0.0f, 1.0f);// basically tells which axis to the face would be on
			
			glTexCoord2f(b1, b2);
			glVertex3f(4.5f, -4.5f, 4.5f);

			glTexCoord2f(b1, b2 + off);
			glVertex3f(4.5f, 4.5f, 4.5f);

			glTexCoord2f(b1 + off, b2 + off);
			glVertex3f(-4.5f, 4.5f, 4.5f);

			glTexCoord2f(b1 + off, b2);
			glVertex3f(-4.5f, -4.5f, 4.5f);

			// right
			// glColor3f(c1, c2, c3);//color of the surface
			glNormal3f(1.0f, 0.0f, 0.0f);// basically tells which axis to the face would be on
			
			glTexCoord2f(c1, c2);
			glVertex3f(4.5f, 4.5f, -4.5f);
			
			glTexCoord2f(c1, c2 + off);
			glVertex3f(4.5f, 4.5f, 4.5f);

			glTexCoord2f(c1 + off, c2 + off);
			glVertex3f(4.5f, -4.5f, 4.5f);

			glTexCoord2f(c1 + off, c2);
			glVertex3f(4.5f, -4.5f, -4.5f);

			// left
			// glColor3f(d1, d2, d3);//color of the surface
			glNormal3f(-1.0f, 0.0f, 0.0f);// basically tells which axis to the face would be on
			
			glTexCoord2f(d1, d2);
			glVertex3f(-4.5f, -4.5f, 4.5f);

			glTexCoord2f(d1, d2 + off);
			glVertex3f(-4.5f, 4.5f, 4.5f);

			glTexCoord2f(d1 + off, d2 + off);
			glVertex3f(-4.5f, 4.5f, -4.5f);

			glTexCoord2f(d1 + off, d2);
			glVertex3f(-4.5f, -4.5f, -4.5f);
	 
			// bottom
			// glColor3f(e1, e2, e3);//color of the surface
			glNormal3f(0.0f, -1.0f, 0.0f);//// basically tells which axis to the face would be on
			
			glTexCoord2f(e1, e2);
			glVertex3f(4.5f, -4.5f, 4.5f);

			glTexCoord2f(e1, e2 + off);
			glVertex3f(-4.5f, -4.5f, 4.5f);

			glTexCoord2f(e1 + off, e2 + off);
			glVertex3f(-4.5f, -4.5f, -4.5f);

			glTexCoord2f(e1 + off, e2);
			glVertex3f(4.5f, -4.5f, -4.5f);
	 
			// back
			// glColor3f(f1, f2, f3);//color of the surface
			glNormal3f(0.0f, 0.0f, -1.0f);// basically tells which axis to the face would be on
			
			glTexCoord2f(f1, f2);
			glVertex3f(4.5f, 4.5f, -4.5f);

			glTexCoord2f(f1, f2 + off);
			glVertex3f(4.5f, -4.5f, -4.5f);

			glTexCoord2f(f1 + off, f2 + off);
			glVertex3f(-4.5f, -4.5f, -4.5f);

			glTexCoord2f(f1 + off, f2);
			glVertex3f(-4.5f, 4.5f, -4.5f);
	 
	glEnd();

		glFlush();

		glDisable(GL_TEXTURE_2D);
glPopMatrix();
}
////////////////////////////////







void drawcube( float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3, float d1, float d2, float d3, float e1, float e2, float e3, float f1, float f2, float f3) {


glBegin(GL_QUADS);
		// top
		glColor3f(a1, a2, a3);//color of the surface
		glNormal3f(0.0f, 1.0f, 0.0f);// basically tells which axis to the face would be on
		glVertex3f(-4.5f, 4.5f, 4.5f);
		glVertex3f(4.5f, 4.5f, 4.5f);
		glVertex3f(4.5f, 4.5f, -4.5f);
		glVertex3f(-4.5f, 4.5f, -4.5f);

		// front
		glColor3f(b1, b2, b3);//color of the surface
		glNormal3f(0.0f, 0.0f, 1.0f);// basically tells which axis to the face would be on
		glVertex3f(4.5f, -4.5f, 4.5f);
		glVertex3f(4.5f, 4.5f, 4.5f);
		glVertex3f(-4.5f, 4.5f, 4.5f);
		glVertex3f(-4.5f, -4.5f, 4.5f);

		// right
		glColor3f(c1, c2, c3);//color of the surface
		glNormal3f(1.0f, 0.0f, 0.0f);// basically tells which axis to the face would be on
		glVertex3f(4.5f, 4.5f, -4.5f);
		glVertex3f(4.5f, 4.5f, 4.5f);
		glVertex3f(4.5f, -4.5f, 4.5f);
		glVertex3f(4.5f, -4.5f, -4.5f);

		// left
		glColor3f(d1, d2, d3);//color of the surface
		glNormal3f(-1.0f, 0.0f, 0.0f);// basically tells which axis to the face would be on
		glVertex3f(-4.5f, -4.5f, 4.5f);
		glVertex3f(-4.5f, 4.5f, 4.5f);
		glVertex3f(-4.5f, 4.5f, -4.5f);
		glVertex3f(-4.5f, -4.5f, -4.5f);
 
		// bottom
		glColor3f(e1, e2, e3);//color of the surface
		glNormal3f(0.0f, -1.0f, 0.0f);//// basically tells which axis to the face would be on
		glVertex3f(4.5f, -4.5f, 4.5f);
		glVertex3f(-4.5f, -4.5f, 4.5f);
		glVertex3f(-4.5f, -4.5f, -4.5f);
		glVertex3f(4.5f, -4.5f, -4.5f);
 
		// back
		glColor3f(f1, f2, f3);//color of the surface
		glNormal3f(0.0f, 0.0f, -1.0f);// basically tells which axis to the face would be on
		glVertex3f(4.5f, 4.5f, -4.5f);
		glVertex3f(4.5f, -4.5f, -4.5f);
		glVertex3f(-4.5f, -4.5f, -4.5f);
		glVertex3f(-4.5f, 4.5f, -4.5f);
 
glEnd();

}


void drawAxes() {
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);
	glEnd();

	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);
	glEnd();

	glColor3d(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);
	glEnd();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 120.0);
	glMatrixMode(GL_MODELVIEW);
	camera();
}


void camera() {
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -55.0);
	glRotatef(cam_xrot, 1, 0, 0);
	glRotatef(cam_yrot, 0, 1, 0);
	glRotatef(cam_zrot, 0, 0, 1);
}


void keyboard(unsigned char key, int x, int y)
{
	// Camera controls - Rotation along principle axis
	switch (key) {

	case 'p':
		prevRot = rotation;
		rotation = 3;
		keyPressed = 'p';
		phi += 2;

			if ((abs(phi) == 90)||(abs(phi) == 180)||(abs(phi) == 270)||(abs(phi) == 360))
			{
				eChange += offC;
				for (int x = 0; x < forL; x = x + 2)
				{

				nice0 = v1[0];
				nice1 = v1[1];
				nice2 = v1[2];
				nice3 = v1[3];
				nice4 = v1[4];
				nice5 = v1[5];
				nice6 = v1[6];
				nice7 = v1[7];
				nice10 = v1[10];
				nice11 = v1[11];
				nice12 = v1[12];
				nice13 = v1[13];
				nice14 = v1[14];
				nice15 = v1[15];
				nice16 = v1[16];
				nice17 = v1[17];


				v1[4] = nice16;
				v1[5] = nice17;
				v1[10] = nice14;
				v1[11] = nice15;
				v1[16] = nice12;
				v1[17] = nice13;
				v1[14] = nice6;
				v1[15] = nice7;
				v1[12] = nice0;
				v1[13] = nice1;
				v1[6] = nice2;
				v1[7] = nice3;
				v1[0] = nice4;
				v1[1] = nice5;
				v1[2] = nice10;
				v1[3] = nice11;

				poop1 = v6[0]; 
				poop2 = v6[1]; 
				poop3 = v6[2]; 
				poop4 = v6[3]; 
				poop5 = v6[4]; 
				poop6 = v6[5];

				v6[0] = v2[0];
				v6[1] = v2[1];
				v6[2] = v2[2];
				v6[3] = v2[3];
				v6[4] = v2[4];
				v6[5] = v2[5];

				v2[0] = v5[0];
				v2[1] = v5[1];
				v2[2] = v5[2];
				v2[3] = v5[3];
				v2[4] = v5[4];
				v2[5] = v5[5];

				v5[0] = v4[16];
				v5[1] = v4[17];
				v5[2] = v4[14];
				v5[3] = v4[15];
				v5[4] = v4[12];
				v5[5] = v4[13];


				v4[16] =  poop1;
				v4[17] =  poop2;
				v4[14] =  poop3;
				v4[15] =  poop4;
				v4[12] = poop5;
				v4[13] = poop6;

				int i = myarray[x][0][0];
				int j = myarray[x][0][1];
				int k = myarray[x][0][2];
				
				myarray[x][0][0] = myarray[x][0][0];
				myarray[x][0][1] = myarray[x][1][0];
				myarray[x][0][2] = myarray[x][2][0];

				myarray[x][0][0] = myarray[x][2][0];
				myarray[x][1][0] = myarray[x][2][1];
				myarray[x][2][0] = myarray[x][2][2];

				myarray[x][2][0] = myarray[x][0][2];
				myarray[x][2][1] = myarray[x][1][2];
				myarray[x][2][2] = myarray[x][2][2];
				
				myarray[x][0][2] = i;
				myarray[x][1][2] = j;
				myarray[x][2][2] = k;
				}
			}


		if (phi >= reset){ 

			// rotation = 3;
			if ((phi == 90)||(phi == 180)||(phi == 270)||(phi == 360))
			{
				// counterP = 1;
				// changerBB -= offC;
				// changerGG -= offC;
			}

			// changerPP += offC;
			jump = 2;
			phi = reseter;
		}
		break;

	case 'P':
		prevRot = rotation;
		rotation = -3;
		keyPressed = 'P';
		phi -= 2;
			if ((abs(phi) == 90)||(abs(phi) == 180)||(abs(phi) == 270)||(abs(phi) == 360))
			{
				eChange -= offC;
				for (int x = 0; x < forL; x = x + 2)
				{
			
				nice0 = v1[0];
				nice1 = v1[1];
				nice2 = v1[2];
				nice3 = v1[3];
				nice4 = v1[4];
				nice5 = v1[5];
				nice6 = v1[6];
				nice7 = v1[7];
				nice10 = v1[10];
				nice11 = v1[11];
				nice12 = v1[12];
				nice13 = v1[13];
				nice14 = v1[14];
				nice15 = v1[15];
				nice16 = v1[16];
				nice17 = v1[17];


				v1[4] = nice0;
				v1[5] = nice1;
				v1[10] = nice2;
				v1[11] = nice3;
				v1[16] = nice4;
				v1[17] = nice5;
				v1[14] = nice10;
				v1[15] = nice11;
				v1[12] = nice16;
				v1[13] = nice17;
				v1[6] = nice14;
				v1[7] = nice15;
				v1[0] = nice12;
				v1[1] = nice13;
				v1[2] = nice6;
				v1[3] = nice7;
				
				poop1 = v2[0]; 
				poop2 = v2[1]; 
				poop3 = v2[2]; 
				poop4 = v2[3]; 
				poop5 = v2[4]; 
				poop6 = v2[5];

				v2[0] = v6[0];
				v2[1] = v6[1];
				v2[2] = v6[2];
				v2[3] = v6[3];
				v2[4] = v6[4];
				v2[5] = v6[5];

				v6[0] = v4[16];
				v6[1] = v4[17];
				v6[2] = v4[14];
				v6[3] = v4[15];
				v6[4] = v4[12];
				v6[5] = v4[13];

				v4[16] = v5[0];
				v4[17] = v5[1];
				v4[14] = v5[2];
				v4[15] = v5[3];
				v4[12] = v5[4];
				v4[13] = v5[5];


				v5[0] =  poop1;
				v5[1] =  poop2;
				v5[2] =  poop3;
				v5[3] =  poop4;
				v5[4] = poop5;
				v5[5] = poop6;


				int i = myarray[x][0][0];
				int j = myarray[x][0][1];
				int k = myarray[x][0][2];
				
				myarray[x][0][0] = myarray[x][0][2];
				myarray[x][0][1] = myarray[x][1][2];
				myarray[x][0][2] = myarray[x][2][2];

				myarray[x][0][2] = myarray[x][2][0];
				myarray[x][1][2] = myarray[x][2][1];
				myarray[x][2][2] = myarray[x][2][2];

				myarray[x][2][0] = myarray[x][0][0];
				myarray[x][2][1] = myarray[x][1][0];
				myarray[x][2][2] = myarray[x][2][0];

				myarray[x][0][0] = i;
				myarray[x][1][0] = j;
				myarray[x][2][0] = k;
				}
			}
		if (phi <= -reset){

		// rotation = -3;
		// if (((phi == -90)||(phi == -180)||(phi == -270)||(phi == -360)))
		// {
		// 	changerBB += offC;
		// 	changerGG += offC;
		// }
		// changerPP -= offC;
		jump = 2;
		phi = reseter;
		}
		break;

	case 'o':
		prevRot = rotation;
		rotation = 6;
		keyPressed = 'o';
		phi1 += 2;	
		if ((abs(phi1) == 90)||(abs(phi1) == 180)||(abs(phi1) == 270)||(abs(phi1) == 360))
			{	
			eChange += offC;		
			for (int x = forl; x < 3; x = x + 2)
				{
			
				nice0 = v3[0];
				nice1 = v3[1];
				nice2 = v3[2];
				nice3 = v3[3];
				nice4 = v3[4];
				nice5 = v3[5];
				nice6 = v3[6];
				nice7 = v3[7];
				nice10 = v3[10];
				nice11 = v3[11];
				nice12 = v3[12];
				nice13 = v3[13];
				nice14 = v3[14];
				nice15 = v3[15];
				nice16 = v3[16];
				nice17 = v3[17];


				v3[4] = nice0;
				v3[5] = nice1;
				v3[10] = nice2;
				v3[11] = nice3;
				v3[16] = nice4;
				v3[17] = nice5;
				v3[14] = nice10;
				v3[15] = nice11;
				v3[12] = nice16;
				v3[13] = nice17;
				v3[6] = nice14;
				v3[7] = nice15;
				v3[0] = nice12;
				v3[1] = nice13;
				v3[2] = nice6;
				v3[3] = nice7;
				
				poop1 = v6[12]; 
				poop2 = v6[13]; 
				poop3 = v6[14]; 
				poop4 = v6[15]; 
				poop5 = v6[16]; 
				poop6 = v6[17];

				v6[12] = v2[12];
				v6[13] = v2[13];
				v6[14] = v2[14];
				v6[15] = v2[15];
				v6[16] = v2[16];
				v6[17] = v2[17];

				v2[12] = v5[12];
				v2[13] = v5[13];
				v2[14] = v5[14];
				v2[15] = v5[15];
				v2[16] = v5[16];
				v2[17] = v5[17];

				v5[12] = v4[4];
				v5[13] = v4[5];
				v5[14] = v4[2];
				v5[15] = v4[3];
				v5[16] = v4[0];
				v5[17] = v4[1];


				v4[4] =  poop1;
				v4[5] =  poop2;
				v4[2] =  poop3;
				v4[3] =  poop4;
				v4[0] = poop5;
				v4[1] = poop6;

				int i = myarray[x][0][0];
				int j = myarray[x][0][1];
				int k = myarray[x][0][2];
				
				myarray[x][0][0] = myarray[x][0][0];
				myarray[x][0][1] = myarray[x][1][0];
				myarray[x][0][2] = myarray[x][2][0];

				myarray[x][0][0] = myarray[x][2][0];
				myarray[x][1][0] = myarray[x][2][1];
				myarray[x][2][0] = myarray[x][2][2];

				myarray[x][2][0] = myarray[x][0][2];
				myarray[x][2][1] = myarray[x][1][2];
				myarray[x][2][2] = myarray[x][2][2];
				
				myarray[x][0][2] = i;
				myarray[x][1][2] = j;
				myarray[x][2][2] = k;
				}
			}
		if (phi1 >= reset){ 

			// rotation = 3;
			// changerPp += offC;
			jump = 2;
			phi1 = reseter;
		}
		break;

	case 'O':
		prevRot = rotation;
		rotation = -6;
		keyPressed = 'O';
		phi1 -= 2;
		if ((abs(phi1) == 90)||(abs(phi1) == 180)||(abs(phi1) == 270)||(abs(phi1) == 360))
			{
				eChange -= offC;
				for (int x = forl; x < 3; x = x + 2)
				{
			
				nice0 = v3[0];
				nice1 = v3[1];
				nice2 = v3[2];
				nice3 = v3[3];
				nice4 = v3[4];
				nice5 = v3[5];
				nice6 = v3[6];
				nice7 = v3[7];
				nice10 = v3[10];
				nice11 = v3[11];
				nice12 = v3[12];
				nice13 = v3[13];
				nice14 = v3[14];
				nice15 = v3[15];
				nice16 = v3[16];
				nice17 = v3[17];


				v3[4] = nice16;
				v3[5] = nice17;
				v3[10] = nice14;
				v3[11] = nice15;
				v3[16] = nice12;
				v3[17] = nice13;
				v3[14] = nice6;
				v3[15] = nice7;
				v3[12] = nice0;
				v3[13] = nice1;
				v3[6] = nice2;
				v3[7] = nice3;
				v3[0] = nice4;
				v3[1] = nice5;
				v3[2] = nice10;
				v3[3] = nice11;

				poop1 = v2[12]; 
				poop2 = v2[13]; 
				poop3 = v2[14]; 
				poop4 = v2[15]; 
				poop5 = v2[16]; 
				poop6 = v2[17];

				v2[12] = v6[12];
				v2[13] = v6[13];
				v2[14] = v6[14];
				v2[15] = v6[15];
				v2[16] = v6[16];
				v2[17] = v6[17];

				v6[12] = v4[4];
				v6[13] = v4[5];
				v6[14] = v4[2];
				v6[15] = v4[3];
				v6[16] = v4[0];
				v6[17] = v4[1];

				v4[4] = v5[12];
				v4[5] = v5[13];
				v4[2] = v5[14];
				v4[3] = v5[15];
				v4[0] = v5[16];
				v4[1] = v5[17];


				v5[12] =  poop1;
				v5[13] =  poop2;
				v5[14] =  poop3;
				v5[15] =  poop4;
				v5[16] = poop5;
				v5[17] = poop6;

				int i = myarray[x][0][0];
				int j = myarray[x][0][1];
				int k = myarray[x][0][2];
				
				myarray[x][0][0] = myarray[x][0][2];
				myarray[x][0][1] = myarray[x][1][2];
				myarray[x][0][2] = myarray[x][2][2];

				myarray[x][0][2] = myarray[x][2][0];
				myarray[x][1][2] = myarray[x][2][1];
				myarray[x][2][2] = myarray[x][2][2];

				myarray[x][2][0] = myarray[x][0][0];
				myarray[x][2][1] = myarray[x][1][0];
				myarray[x][2][2] = myarray[x][2][0];

				myarray[x][0][0] = i;
				myarray[x][1][0] = j;
				myarray[x][2][0] = k;
				}
			}
		if (phi1 <= -reset){

		// rotation = -3;
		// changerPp -= offC;
		jump = 2;
		phi1 = reseter;
		}
		break;
		
	case 'g':
		prevRot = rotation;
		rotation = 1;
		keyPressed = 'g';
		gamma += 2;
		// if (gamma >360) gamma -= 360;
		if (gamma != 0) {
			// gamma = gamma + 2;
			// keybd_event(VkKeyScan('g'),0xa2,0 , 0); //
			// bot.KeyDown(0x47);
			if ((abs(gamma) == 90)||(abs(gamma) == 180)||(abs(gamma) == 270)||(abs(gamma) == 360))
			{
				eChange += offC;
				for (int x = 0; x < forL; x = x + 2)
				{
			
				
				nice0 = v2[0];
				nice1 = v2[1];
				nice2 = v2[2];
				nice3 = v2[3];
				nice4 = v2[4];
				nice5 = v2[5];
				nice6 = v2[6];
				nice7 = v2[7];
				nice10 = v2[10];
				nice11 = v2[11];
				nice12 = v2[12];
				nice13 = v2[13];
				nice14 = v2[14];
				nice15 = v2[15];
				nice16 = v2[16];
				nice17 = v2[17];


				v2[4] = nice16;
				v2[5] = nice17;
				v2[10] = nice14;
				v2[11] = nice15;
				v2[16] = nice12;
				v2[17] = nice13;
				v2[14] = nice6;
				v2[15] = nice7;
				v2[12] = nice0;
				v2[13] = nice1;
				v2[6] = nice2;
				v2[7] = nice3;
				v2[0] = nice4;
				v2[1] = nice5;
				v2[2] = nice10;
				v2[3] = nice11;

				poop1 = v1[12]; 
				poop2 = v1[13]; 
				poop3 = v1[14]; 
				poop4 = v1[15]; 
				poop5 = v1[16]; 
				poop6 = v1[17];

				v1[12] = v6[0];
				v1[13] = v6[1];
				v1[14] = v6[6];
				v1[15] = v6[7];
				v1[16] = v6[12];
				v1[17] = v6[13];

				v6[0] = v3[4];
				v6[1] = v3[5];
				v6[6] = v3[2];
				v6[7] = v3[3];
				v6[12] = v3[0];
				v6[13] = v3[1];

				v3[4] = v5[16];
				v3[5] = v5[17];
				v3[2] = v5[10];
				v3[3] = v5[11];
				v3[0] = v5[4];
				v3[1] = v5[5];


				v5[16] =  poop1;
				v5[17] =  poop2;
				v5[10] =  poop3;
				v5[11] =  poop4;
				v5[4] = poop5;
				v5[5] = poop6;

				int i = myarray[0][0][x];
				int j = myarray[1][0][x];
				int k = myarray[2][0][x];
				
				myarray[0][0][x] = myarray[0][0][x];
				myarray[1][0][x] = myarray[0][1][x];
				myarray[2][0][x] = myarray[0][2][x];

				myarray[0][0][x] = myarray[0][2][x];
				myarray[0][1][x] = myarray[1][2][x];
				myarray[0][2][x] = myarray[2][2][x];

				myarray[0][2][x] = myarray[2][0][x];
				myarray[1][2][x] = myarray[2][1][x];
				myarray[2][2][x] = myarray[2][2][x];
				
				myarray[2][0][x] = i;
				myarray[2][1][x] = j;
				myarray[2][2][x] = k;
				}
			}
			if (gamma >= reset)
			{


				// checker = checker - 10;
			// changerGG += offC;
			// if ((gamma == 90)||(gamma == 180)||(gamma == 270)||(gamma == 360))
			// {
			// 	changerBB -= offC;
			// 	changerPP -= offC;
			// }
				// rotation = 1;
				jump = 0;
				gamma = reseter;
			}
			//glutPostRedisplay();
		}
		break;

	case 'G':
		prevRot = rotation;
		rotation = -1;
		keyPressed = 'G';
		gamma += -2;
		// if (gamma < -360) gamma += 360;
		if (gamma != 0) {
			// gamma = gamma - 2;
			if ((abs(gamma) == 90)||(abs(gamma) == 180)||(abs(gamma) == 270)||(abs(gamma) == 360))
			{
				eChange -= offC;
				for (int x = 0; x < forL; x = x + 2)
				{
			
				nice0 = v2[0];
				nice1 = v2[1];
				nice2 = v2[2];
				nice3 = v2[3];
				nice4 = v2[4];
				nice5 = v2[5];
				nice6 = v2[6];
				nice7 = v2[7];
				nice10 = v2[10];
				nice11 = v2[11];
				nice12 = v2[12];
				nice13 = v2[13];
				nice14 = v2[14];
				nice15 = v2[15];
				nice16 = v2[16];
				nice17 = v2[17];


				v2[4] = nice0;
				v2[5] = nice1;
				v2[10] = nice2;
				v2[11] = nice3;
				v2[16] = nice4;
				v2[17] = nice5;
				v2[14] = nice10;
				v2[15] = nice11;
				v2[12] = nice16;
				v2[13] = nice17;
				v2[6] = nice14;
				v2[7] = nice15;
				v2[0] = nice12;
				v2[1] = nice13;
				v2[2] = nice6;
				v2[3] = nice7;
				
				poop1 = v1[12]; 
				poop2 = v1[13]; 
				poop3 = v1[14]; 
				poop4 = v1[15]; 
				poop5 = v1[16]; 
				poop6 = v1[17];

				v1[12] = v5[16];
				v1[13] = v5[17];
				v1[14] = v5[10];
				v1[15] = v5[11];
				v1[16] = v5[4];
				v1[17] = v5[5];

				v5[16]= v3[4];
				v5[17]= v3[5];
				v5[10]= v3[2];
				v5[11]= v3[3];
				v5[4] = v3[0];
				v5[5] = v3[1];

				v3[4] = v6[0];
				v3[5] = v6[1];
				v3[2] = v6[6];
				v3[3] = v6[7];
				v3[0] = v6[12];
				v3[1] = v6[13];


				v6[0] =  poop1;
				v6[1] =  poop2;
				v6[6] =  poop3;
				v6[7] =  poop4;
				v6[12] = poop5;
				v6[13] = poop6;

				int i = myarray[0][0][x];
				int j = myarray[1][0][x];
				int k = myarray[2][0][x];
				
				myarray[0][0][x] = myarray[2][0][x];
				myarray[1][0][x] = myarray[2][1][x];
				myarray[2][0][x] = myarray[2][2][x];

				myarray[2][0][x] = myarray[0][2][x];
				myarray[2][1][x] = myarray[1][2][x];
				myarray[2][2][x] = myarray[2][2][x];

				myarray[0][2][x] = myarray[0][0][x];
				myarray[1][2][x] = myarray[0][1][x];
				myarray[2][2][x] = myarray[0][2][x];

				myarray[0][0][x] = i;
				myarray[0][1][x] = j;
				myarray[0][2][x] = k;
				}
			}
			if (gamma <= -reset)
			{

			// changerGG -= offC;
			// if ((gamma == -90)||(gamma == -180)||(gamma == -270)||(gamma == -360))
			// {
			// 	changerBB += offC;
			// 	changerPP += offC;
			// }
				// rotation = -1;
				jump = 0;
				gamma = reseter;
			}
			// glutPostRedisplay();
		}
		break;

	case 'h':
		prevRot = rotation;
		rotation = 4;
		keyPressed = 'h';
		gamma1 += 2;
			if ((abs(gamma1) == 90)||(abs(gamma1) == 180)||(abs(gamma1) == 270)||(abs(gamma1) == 360))
			{			
			eChange += offC;	
				for (int x = forl; x < 3; x = x + 2)
				{
			
				
				nice0 = v4[0];
				nice1 = v4[1];
				nice2 = v4[2];
				nice3 = v4[3];
				nice4 = v4[4];
				nice5 = v4[5];
				nice6 = v4[6];
				nice7 = v4[7];
				nice10 = v4[10];
				nice11 = v4[11];
				nice12 = v4[12];
				nice13 = v4[13];
				nice14 = v4[14];
				nice15 = v4[15];
				nice16 = v4[16];
				nice17 = v4[17];


				v4[4] = nice0;
				v4[5] = nice1;
				v4[10] = nice2;
				v4[11] = nice3;
				v4[16] = nice4;
				v4[17] = nice5;
				v4[14] = nice10;
				v4[15] = nice11;
				v4[12] = nice16;
				v4[13] = nice17;
				v4[6] = nice14;
				v4[7] = nice15;
				v4[0] = nice12;
				v4[1] = nice13;
				v4[2] = nice6;
				v4[3] = nice7;

				poop1 = v1[0]; 
				poop2 = v1[1]; 
				poop3 = v1[2]; 
				poop4 = v1[3]; 
				poop5 = v1[4]; 
				poop6 = v1[5];

				v1[0] = v6[4];
				v1[1] = v6[5];
				v1[2] = v6[10];
				v1[3] = v6[11];
				v1[4] = v6[16];
				v1[5] = v6[17];

				v6[4] = v3[16];
				v6[5] = v3[17];
				v6[10] = v3[14];
				v6[11] = v3[15];
				v6[16] = v3[12];
				v6[17] = v3[13];

				v3[16] = v5[12];
				v3[17] = v5[13];
				v3[14] = v5[6];
				v3[15] = v5[7];
				v3[12] = v5[0];
				v3[13] = v5[1];


				v5[12] =  poop1;
				v5[13] =  poop2;
				v5[6] =  poop3;
				v5[7] =  poop4;
				v5[0] = poop5;
				v5[1] = poop6;

				int i = myarray[0][0][x];
				int j = myarray[1][0][x];
				int k = myarray[2][0][x];
				
				myarray[0][0][x] = myarray[0][0][x];
				myarray[1][0][x] = myarray[0][1][x];
				myarray[2][0][x] = myarray[0][2][x];

				myarray[0][0][x] = myarray[0][2][x];
				myarray[0][1][x] = myarray[1][2][x];
				myarray[0][2][x] = myarray[2][2][x];

				myarray[0][2][x] = myarray[2][0][x];
				myarray[1][2][x] = myarray[2][1][x];
				myarray[2][2][x] = myarray[2][2][x];
				
				myarray[2][0][x] = i;
				myarray[2][1][x] = j;
				myarray[2][2][x] = k;
				}
			}

		// if (gamma1 >360) gamma1 -= 360;
		if (gamma1 != 0) {
			// gamma1 = gamma1 + 2;
			// keybd_event(VkKeyScan('g'),0xa2,0 , 0); //
			// bot.KeyDown(0x47);

			if (gamma1 >= reset)
			{


				// checker = checker - 10;
				// changerGg += offC;
				// if(changerG == 1.0){
				// 	changerG = 0.0;
				// }
				// rotation = 1;
				jump = 0;
				gamma1 = reseter;
			}
			//glutPostRedisplay();
		}
		break;

	case 'H':
		prevRot = rotation;
		rotation = -4;
		keyPressed = 'H';
		gamma1 += -2;
			if ((abs(gamma1) == 90)||(abs(gamma1) == 180)||(abs(gamma1) == 270)||(abs(gamma1) == 360))
			{		
			eChange -= offC;		
				for (int x = forl; x < 3; x = x + 2)
				{
			
				nice0 = v4[0];
				nice1 = v4[1];
				nice2 = v4[2];
				nice3 = v4[3];
				nice4 = v4[4];
				nice5 = v4[5];
				nice6 = v4[6];
				nice7 = v4[7];
				nice10 = v4[10];
				nice11 = v4[11];
				nice12 = v4[12];
				nice13 = v4[13];
				nice14 = v4[14];
				nice15 = v4[15];
				nice16 = v4[16];
				nice17 = v4[17];


				v4[4] = nice16;
				v4[5] = nice17;
				v4[10] = nice14;
				v4[11] = nice15;
				v4[16] = nice12;
				v4[17] = nice13;
				v4[14] = nice6;
				v4[15] = nice7;
				v4[12] = nice0;
				v4[13] = nice1;
				v4[6] = nice2;
				v4[7] = nice3;
				v4[0] = nice4;
				v4[1] = nice5;
				v4[2] = nice10;
				v3[3] = nice11;
				
				poop1 = v1[4]; 
				poop2 = v1[5]; 
				poop3 = v1[2]; 
				poop4 = v1[3]; 
				poop5 = v1[0]; 
				poop6 = v1[1];

				v1[4] = v5[0];
				v1[5] = v5[1];
				v1[2] = v5[6];
				v1[3] = v5[7];
				v1[0] = v5[12];
				v1[1] = v5[13];

				v5[0]= v3[12];
				v5[1]= v3[13];
				v5[6]= v3[14];
				v5[7]= v3[15];
				v5[12]= v3[16];
				v5[13]= v3[17];

				v3[12] = v6[16];
				v3[13] = v6[17];
				v3[14] = v6[10];
				v3[15] = v6[11];
				v3[16] = v6[4];
				v3[17] = v6[5];


				v6[16] =  poop1;
				v6[17] =  poop2;
				v6[10] =  poop3;
				v6[11] =  poop4;
				v6[4] = poop5;
				v6[5] = poop6;


				int i = myarray[0][0][x];
				int j = myarray[1][0][x];
				int k = myarray[2][0][x];
				
				myarray[0][0][x] = myarray[2][0][x];
				myarray[1][0][x] = myarray[2][1][x];
				myarray[2][0][x] = myarray[2][2][x];

				myarray[2][0][x] = myarray[0][2][x];
				myarray[2][1][x] = myarray[1][2][x];
				myarray[2][2][x] = myarray[2][2][x];

				myarray[0][2][x] = myarray[0][0][x];
				myarray[1][2][x] = myarray[0][1][x];
				myarray[2][2][x] = myarray[0][2][x];

				myarray[0][0][x] = i;
				myarray[0][1][x] = j;
				myarray[0][2][x] = k;
				}
			}
		// if (gamma1 < -360) gamma1 += 360;
		if (gamma1 != 0) {
			// gamma1 = gamma1 - 2;

			if (gamma1 <= -reset)
			{

				// changerGg -= offC;
				// if(changerG == -1.0){
				// 	changerG = 0.0;
				// }
				// rotation = -1;
				jump = 0;
				gamma1 = reseter;
			}
			// glutPostRedisplay();
		}
		break;






	case 'b':
		prevRot = rotation;
		rotation = 2;
		keyPressed = 'b';
		beta += 2;
		if ((abs(beta) == 90)||(abs(beta) == 180)||(abs(beta) == 270)||(abs(beta) == 360))
		{
				eChange += offC;
				for (int x = 0; x < forL; x = x + 2)
				{
				////////////////////////////////////////////////
				
				nice0 = v5[0];
				nice1 = v5[1];
				nice2 = v5[2];
				nice3 = v5[3];
				nice4 = v5[4];
				nice5 = v5[5];
				nice6 = v5[6];
				nice7 = v5[7];
				nice10 = v5[10];
				nice11 = v5[11];
				nice12 = v5[12];
				nice13 = v5[13];
				nice14 = v5[14];
				nice15 = v5[15];
				nice16 = v5[16];
				nice17 = v5[17];


				v5[4] = nice0;
				v5[5] = nice1;
				v5[10] = nice2;
				v5[11] = nice3;
				v5[16] = nice4;
				v5[17] = nice5;
				v5[14] = nice10;
				v5[15] = nice11;
				v5[12] = nice16;
				v5[13] = nice17;
				v5[6] = nice14;
				v5[7] = nice15;
				v5[0] = nice12;
				v5[1] = nice13;
				v5[2] = nice6;
				v5[3] = nice7;

				poop1 = v1[0]; 
				poop2 = v1[1]; 
				poop3 = v1[6]; 
				poop4 = v1[7]; 
				poop5 = v1[12]; 
				poop6 = v1[13];

				v1[0] = v4[0];
				v1[1] = v4[1];
				v1[6] = v4[6];
				v1[7] = v4[7];
				v1[12] = v4[12];
				v1[13] = v4[13];

				v4[0] = v3[0];
				v4[1] = v3[1];
				v4[6] = v3[6];
				v4[7] = v3[7];
				v4[12] = v3[12];
				v4[13] = v3[13];

				v3[0] = v2[0];
				v3[1] = v2[1];
				v3[6] = v2[6];
				v3[7] = v2[7];
				v3[12] = v2[12];
				v3[13] = v2[13];


				v2[0] = poop1;
				v2[1] = poop2;
				v2[6] = poop3;
				v2[7] = poop4;
				v2[12] =poop5;
				v2[13] =poop6;

				/////////////////////////////////////////////////



				int i = myarray[0][x][0];
				int j = myarray[1][x][0];
				int k = myarray[2][x][0];
				
				myarray[0][x][0] = myarray[0][x][0];
				myarray[1][x][0] = myarray[0][x][1];
				myarray[2][x][0] = myarray[0][x][2];

				myarray[0][x][0] = myarray[0][x][2];
				myarray[0][x][1] = myarray[1][x][2];
				myarray[0][x][2] = myarray[2][x][2];

				myarray[0][x][2] = myarray[2][x][0];
				myarray[1][x][2] = myarray[2][x][1];
				myarray[2][x][2] = myarray[2][x][2];
				
				myarray[2][x][0] = i;
				myarray[2][x][1] = j;
				myarray[2][x][2] = k;
				}
		}
		if (beta >= reset){ 

			// rotation = 2;
			// changerBB += offC;
			// if ((beta == 90)||(beta == 180)||(beta == 270)||(beta == 360))
			// {
			// 	changerGG -= offC;
			// 	changerPP -= offC;
			// }
			jump = 1;
			beta = reseter;
		}
		break;

	case 'B':
		prevRot = rotation;
		rotation = -2;
		keyPressed = 'B';
		beta += -2;
			if ((abs(beta) == 90)||(abs(beta) == 180)||(abs(beta) == 270)||(abs(beta) == 360))
			{
				eChange -= offC;
				for (int x = 0; x < forL; x = x + 2)
				{

				nice0 = v5[0];
				nice1 = v5[1];
				nice2 = v5[2];
				nice3 = v5[3];
				nice4 = v5[4];
				nice5 = v5[5];
				nice6 = v5[6];
				nice7 = v5[7];
				nice10 = v5[10];
				nice11 = v5[11];
				nice12 = v5[12];
				nice13 = v5[13];
				nice14 = v5[14];
				nice15 = v5[15];
				nice16 = v5[16];
				nice17 = v5[17];


				v5[4] = nice16;
				v5[5] = nice17;
				v5[10] = nice14;
				v5[11] = nice15;
				v5[16] = nice12;
				v5[17] = nice13;
				v5[14] = nice6;
				v5[15] = nice7;
				v5[12] = nice0;
				v5[13] = nice1;
				v5[6] = nice2;
				v5[7] = nice3;
				v5[0] = nice4;
				v5[1] = nice5;
				v5[2] = nice10;
				v5[3] = nice11;

				poop1 = v1[0]; 
				poop2 = v1[1]; 
				poop3 = v1[6]; 
				poop4 = v1[7]; 
				poop5 = v1[12]; 
				poop6 = v1[13];

				v1[0] = v2[0];
				v1[1] = v2[1];
				v1[6] = v2[6];
				v1[7] = v2[7];
				v1[12] = v2[12];
				v1[13] = v2[13];

				v2[0] = v3[0];
				v2[1] = v3[1];
				v2[6] = v3[6];
				v2[7] = v3[7];
				v2[12] = v3[12];
				v2[13] = v3[13];

				v3[0] = v4[0];
				v3[1] = v4[1];
				v3[6] = v4[6];
				v3[7] = v4[7];
				v3[12] = v4[12];
				v3[13] = v4[13];


				v4[0] = poop1;
				v4[1] = poop2;
				v4[6] = poop3;
				v4[7] = poop4;
				v4[12] =poop5;
				v4[13] =poop6;
				
				int i = myarray[0][x][0];
				int j = myarray[1][x][0];
				int k = myarray[2][x][0];
				
				myarray[0][x][0] = myarray[2][x][0];
				myarray[1][x][0] = myarray[2][x][1];
				myarray[2][x][0] = myarray[2][x][2];

				myarray[2][x][0] = myarray[0][x][2];
				myarray[2][x][1] = myarray[1][x][2];
				myarray[2][x][2] = myarray[2][x][2];

				myarray[0][x][2] = myarray[0][x][0];
				myarray[1][x][2] = myarray[0][x][1];
				myarray[2][x][2] = myarray[0][x][2];

				myarray[0][x][0] = i;
				myarray[0][x][1] = j;
				myarray[0][x][2] = k;
				}
			}
		if (beta <= -reset){ 

				rotation = -2;
			// changerBB -= offC;
			// if ((beta == -90)||(beta == -180)||(beta == -270)||(beta == -360))
			// {
			// 	changerGG += offC;
			// 	changerPP += offC;
			// }
			jump = 1;
			beta = reseter;
		

		}
		break;

	case 'n':
		prevRot = rotation;
		rotation = 5;
		keyPressed = 'n';
		beta1 += 2;
			if ((abs(beta1) == 90)||(abs(beta1) == 180)||(abs(beta1) == 270)||(abs(beta1) == 360))
			{
				eChange += offC;
				for (int x = forl; x < 3; x = x + 2)
				{
			
				nice0 = v6[0];
				nice1 = v6[1];
				nice2 = v6[2];
				nice3 = v6[3];
				nice4 = v6[4];
				nice5 = v6[5];
				nice6 = v6[6];
				nice7 = v6[7];
				nice10 = v6[10];
				nice11 = v6[11];
				nice12 = v6[12];
				nice13 = v6[13];
				nice14 = v6[14];
				nice15 = v6[15];
				nice16 = v6[16];
				nice17 = v6[17];


				v6[4] = nice16;
				v6[5] = nice17;
				v6[10] = nice14;
				v6[11] = nice15;
				v6[16] = nice12;
				v6[17] = nice13;
				v6[14] = nice6;
				v6[15] = nice7;
				v6[12] = nice0;
				v6[13] = nice1;
				v6[6] = nice2;
				v6[7] = nice3;
				v6[0] = nice4;
				v6[1] = nice5;
				v6[2] = nice10;
				v6[3] = nice11;

				poop1 = v1[4]; 
				poop2 = v1[5]; 
				poop3 = v1[10]; 
				poop4 = v1[11]; 
				poop5 = v1[16]; 
				poop6 = v1[17];

				v1[4] = v4[4];
				v1[5] = v4[5];
				v1[10] = v4[10];
				v1[11] = v4[11];
				v1[16] = v4[16];
				v1[17] = v4[17];

				v4[4] = v3[4];
				v4[5] = v3[5];
				v4[10] = v3[10];
				v4[11] = v3[11];
				v4[16] = v3[16];
				v4[17] = v3[17];

				v3[4] = v2[4];
				v3[5] = v2[5];
				v3[10] = v2[10];
				v3[11] = v2[11];
				v3[16] = v2[16];
				v3[17] = v2[17];


				v2[4] = poop1;
				v2[5] = poop2;
				v2[10] = poop3;
				v2[11] = poop4;
				v2[16] =poop5;
				v2[17] =poop6;
				
				int i = myarray[0][x][0];
				int j = myarray[1][x][0];
				int k = myarray[2][x][0];
				
				myarray[0][x][0] = myarray[0][x][0];
				myarray[1][x][0] = myarray[0][x][1];
				myarray[2][x][0] = myarray[0][x][2];

				myarray[0][x][0] = myarray[0][x][2];
				myarray[0][x][1] = myarray[1][x][2];
				myarray[0][x][2] = myarray[2][x][2];

				myarray[0][x][2] = myarray[2][x][0];
				myarray[1][x][2] = myarray[2][x][1];
				myarray[2][x][2] = myarray[2][x][2];
				
				myarray[2][x][0] = i;
				myarray[2][x][1] = j;
				myarray[2][x][2] = k;
				}
			}
		if (beta1 >= reset){ 


			rotation = 2;
			// changerBb += offC;
			// if(changerB == 1.0){
			// 	changerB = 0.0;
			// }
			jump = 1;
			beta1 = reseter;
		}
		break;

	case 'N':
		prevRot = rotation;
		rotation = -5;
		keyPressed = 'N';
		beta1 += -2;
			if ((abs(beta1) == 90)||(abs(beta1) == 180)||(abs(beta1) == 270)||(abs(beta1) == 360))
			{
				eChange -= offC;
				for (int x = forl; x < 3; x = x + 2)
				{

				nice0 = v6[0];
				nice1 = v6[1];
				nice2 = v6[2];
				nice3 = v6[3];
				nice4 = v6[4];
				nice5 = v6[5];
				nice6 = v6[6];
				nice7 = v6[7];
				nice10 = v6[10];
				nice11 = v6[11];
				nice12 = v6[12];
				nice13 = v6[13];
				nice14 = v6[14];
				nice15 = v6[15];
				nice16 = v6[16];
				nice17 = v6[17];


				v6[4] = nice0;
				v6[5] = nice1;
				v6[10] = nice2;
				v6[11] = nice3;
				v6[16] = nice4;
				v6[17] = nice5;
				v6[14] = nice10;
				v6[15] = nice11;
				v6[12] = nice16;
				v6[13] = nice17;
				v6[6] = nice14;
				v6[7] = nice15;
				v6[0] = nice12;
				v6[1] = nice13;
				v6[2] = nice6;
				v6[3] = nice7;

				poop1 = v1[4]; 
				poop2 = v1[5]; 
				poop3 = v1[10]; 
				poop4 = v1[11]; 
				poop5 = v1[16]; 
				poop6 = v1[17];

				v1[4] = v2[4];
				v1[5] = v2[5];
				v1[10] = v2[10];
				v1[11] = v2[11];
				v1[16] = v2[16];
				v1[17] = v2[17];

				v2[4] = v3[4];
				v2[5] = v3[5];
				v2[10] = v3[10];
				v2[11] = v3[11];
				v2[16] = v3[16];
				v2[17] = v3[17];

				v3[4] = v4[4];
				v3[5] = v4[5];
				v3[10] = v4[10];
				v3[11] = v4[11];
				v3[16] = v4[16];
				v3[17] = v4[17];


				v4[4] = poop1;
				v4[5] = poop2;
				v4[10] = poop3;
				v4[11] = poop4;
				v4[16] =poop5;
				v4[17] =poop6;
				
				int i = myarray[0][x][0];
				int j = myarray[1][x][0];
				int k = myarray[2][x][0];
				
				myarray[0][x][0] = myarray[2][x][0];
				myarray[1][x][0] = myarray[2][x][1];
				myarray[2][x][0] = myarray[2][x][2];

				myarray[2][x][0] = myarray[0][x][2];
				myarray[2][x][1] = myarray[1][x][2];
				myarray[2][x][2] = myarray[2][x][2];

				myarray[0][x][2] = myarray[0][x][0];
				myarray[1][x][2] = myarray[0][x][1];
				myarray[2][x][2] = myarray[0][x][2];

				myarray[0][x][0] = i;
				myarray[0][x][1] = j;
				myarray[0][x][2] = k;
				}
			}
		if (beta1 <= -reset){ 

				rotation = -2;
			// changerBb -= offC;
			// if(changerB == -1.0){
			// 	changerB = 0.0;
			// }
			jump = 1;
			beta1 = reseter;
		

		}
		break;

	case 'r': //RESET
		keyPressed = 'r';

		vectorReset();
		vectorinit();

		randomizer = 0;
		phi = 0;
		theta = 0;
		beta = 0;
		gamma = 0;
		phi1 = 0;
		beta1 = 0;
		gamma1 = 0;
		changerPP = 0.0;
		changerBB = 0.0;
		changerGG = 0.0;
		changerPp = 0.0;
		changerBb = 0.0;
		changerGg = 0.0;
		rotation = 0;
		// glutPostRedisplay();
		break; 


	case 't':
		randomizer = 1;

		break;
	case 'T':
		randomizer = 0;
		break;

/////////////////////////////////
	case 'q':
		cam_xrot += 1;
		if (cam_xrot >360) cam_xrot -= 360;
		break;
	case 'z':
		cam_xrot -= 1;
		if (cam_xrot < -360) cam_xrot += 360;
		break;
	case 'a':
		cam_yrot += 1;
		if (cam_yrot >360) cam_yrot -= 360;
		break;
	case 'd':
		cam_yrot -= 1;
		if (cam_yrot < -360) cam_yrot += 360;
		break;
	case 'w':
		cam_zrot += 1;
		if (cam_zrot >360) cam_zrot -= 360;
		break;
	case 'x':
		cam_zrot -= 1;
		if (cam_zrot < -360) cam_zrot += 360;
		break;
	case 27:
		cleanup();
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();

}

///////////////////////////////////////////////////////////
void cleanup() // call once when you exit program
{
	//nothing to clean
}

///////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	vectorinit();
	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////