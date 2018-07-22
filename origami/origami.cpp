// Computer Graphic Project 2017 Jan  
//Heart Origami
//E14031083 伍錫志
#include "stdafx.h"
#include<Windows.h>
#include<gl/GL.H>
#include<gl/GLAUX.H>
#include<gl/glut.h>
#include <cmath>
#include<math.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glaux.lib")
#pragma comment(lib,"glut32.lib")
#define PI 3.1415926
using namespace std;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zRot = 0.0f;
GLfloat fxRot = 0.0f;
GLfloat fyRot = 0.0f;
GLfloat flip = 0.0f;
GLfloat flip1 = 0.0f;
GLfloat flip2 = 0.0f;
GLfloat flip3 = 0.0f;
GLfloat flip4 = 0.0f;
GLfloat flip5 = 0.0f;
GLfloat flip6 = 0.0f;
GLfloat flip7 = 0.0f;
GLfloat flip8 = 0.0f;
GLfloat linewidth = 10;
GLfloat totalangle = 0;
int step1 = 1;
int step2 = 0;
int step3 = 0;
int step4 = 0;
int step5 = 0;
int step6 = 0;
int step7 = 0;
int step8 = 0;
int pic = 2;
int finish = 0;
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the fil
	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:     // Most likely case
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}
GLfloat angle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	GLfloat vecx = abs(x2 - x1);
	GLfloat vecy = abs(y2 - y1);
	GLfloat angle = (atan(vecy / vecx))*(180 / PI);
	return angle;
}
GLfloat angle1 = 135;
GLfloat angle2 = 90;
GLfloat angle3a = 45;
GLfloat angle3b = 0;
GLfloat angle4 = 45;
GLfloat angle5a = 90;
GLfloat angle5b = angle(0, 0, 20, 25);
GLfloat angle6 = 90 + angle(0, 0, 25, 20);
GLfloat angle7 = 0;
GLfloat angle8 = 0;
GLfloat angle9a = 45;
GLfloat angle9b = 0;
GLfloat angle10 = 45;
GLfloat angle11 = 90 + angle(0, 0, 20, 25);
GLfloat angle12a = 0;
GLfloat angle12b = -(90 + angle(0, 0, 20, 25));
GLfloat angle13 = 135;
GLfloat offset1 = 85;

GLbyte *pImage = NULL;
GLbyte *pImage3333 = NULL;
GLbyte *pBytes = NULL;
GLbyte *step11 = NULL;
GLbyte *step22 = NULL;
GLbyte *step33 = NULL;
GLbyte *step44 = NULL;
GLbyte *step55 = NULL;
GLbyte *step66 = NULL;
GLbyte *step77 = NULL;
GLbyte *step88 = NULL;
GLint iWidth;
GLint iHeight;
GLint iComponents;
GLenum eFormat;
GLint iLoop;

void RenderScene(void)
{
	//清除
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (totalangle == 0)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		pImage3333 = gltLoadTGA("start.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (pImage3333 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage3333);

		// Don't need the image data anymore
		free(pImage3333);
		glPopMatrix();
	}
	if (step1 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step11 = gltLoadTGA("step1.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step11 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step11);

		// Don't need the image data anymore
		free(step11);
		glPopMatrix();
	}
	if (step2 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step22 = gltLoadTGA("step2.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step22 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step22);

		// Don't need the image data anymore
		free(step22);
		glPopMatrix();
	}
	if (step3 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step33 = gltLoadTGA("step3.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step33 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step33);

		// Don't need the image data anymore
		free(step33);
		glPopMatrix();
	}
	if (step4 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step44 = gltLoadTGA("step4.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step44 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step44);

		// Don't need the image data anymore
		free(step44);
		glPopMatrix();
	}
	if (step5 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step55 = gltLoadTGA("step5.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step55 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step55);

		// Don't need the image data anymore
		free(step55);
		glPopMatrix();
	}
	if (step6 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step66 = gltLoadTGA("step6.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step66 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step66);

		// Don't need the image data anymore
		free(step66);
		glPopMatrix();
	}
	if (step7 == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step77 = gltLoadTGA("step7.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step77 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step77);

		// Don't need the image data anymore
		free(step77);
		glPopMatrix();
	}
	if (step8 == 1 && finish != 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		step88 = gltLoadTGA("step8.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (step88 != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, step88);

		// Don't need the image data anymore
		free(step88);
		glPopMatrix();
	}
	if (finish == 1)
	{
		glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTranslatef(-275, -150, -100);
		pImage = gltLoadTGA("finish.tga", &iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (pImage != NULL)
			glDrawPixels(iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

		// Don't need the image data anymore
		free(pImage);
		glPopMatrix();
	}
	glPushMatrix();
	//旋轉 	
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-100, -110, 0);
	/////////////////////////////////////////////////  01
	glPushMatrix();
	//glTranslatef(215, 190, 0);
	///////////////////  01  step3
	if (step3 == 1)
	{
		glTranslatef(130, 190, 0);
		glRotatef(-flip3, 0, 1, 0);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();
	}

	if (step4 == 1)
	{
		glTranslatef(130, 190, 0);
		glRotatef(-180, 0, 1, 0);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();
	}
	if (step5 == 1)
	{
		glTranslatef(130, 190, 0);
		glRotatef(-180, 0, 1, 0);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();
	}
	if (step6 == 1)
	{
		glTranslatef(130, 190, 0);
		glRotatef(-180, 0, 1, 0);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(offset1, 0, 0);
		glVertex3f(offset1, 25, 0);
		glVertex3f(offset1 - 25, 25, 0);
		glEnd();
	}
	if (step7 == 1)
	{
		glTranslatef(130 - 85, 20 + 85 + 85, 0);
		glRotatef(-45, 0, 0, 1);
		glRotatef(flip7, 0, 1, 0);
		glRotatef(45, 0, 0, 1);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);
		glEnd();
	}
	if (step8 == 1)
	{
		glTranslatef(130 - 85, 20 + 85 + 85, 0);
		glRotatef(-45, 0, 0, 1);
		glRotatef(180, 0, 1, 0);
		glRotatef(45, 0, 0, 1);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);
		glEnd();
	}
	if (step1 == 1 || step2 == 1)
	{
		glTranslatef(215, 190, 0);
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 25, 0);
		glVertex3f(-25, 25, 0);
		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 25, 0);
		glVertex3f(-25, 25, 0);
		glEnd();
	}

	glPopMatrix();
	/////////////////////////////////////////////////2
	glPushMatrix();
	glTranslatef(130, 85, 0);
	//////////////////////////02 step3
	if (step3 == 1)
	{
		glRotatef(angle2, 0, 0, 1);
		glRotatef(-flip3, 1, 0, 0);
		glRotatef(-angle2, 0, 0, 1);
	}
	if (step4 == 1)
	{
		glRotatef(angle2, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle2, 0, 0, 1);
	}
	if (step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle2, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle2, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(85, 85, 0);
	glVertex3f(85, 105, 0);
	glVertex3f(60, 130, 0);
	glVertex3f(20, 130, 0);
	glVertex3f(0, 105, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(85, 85, 0);
	glVertex3f(85, 105, 0);
	glVertex3f(60, 130, 0);
	glVertex3f(20, 130, 0);
	glVertex3f(0, 105, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////3
	glPushMatrix();
	glTranslatef(130, 85, 0);
	if (step2 == 1)
	{
		glRotatef(angle3a, 0, 0, 1);
		glRotatef(-flip2, 1, 0, 0);
		glRotatef(-angle3a, 0, 0, 1);
	}

	if (step3 == 1)
	{
		///////////////////////////////////
		glRotatef(angle3a, 0, 0, 1);//////保存step2
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle3a, 0, 0, 1);
		//////////////////////////////////
		glRotatef(angle3b, 0, 0, 1);
		glRotatef(-flip3, 1, 0, 0);
		glRotatef(-angle3b, 0, 0, 1);

	}
	if (step4 == 1)
	{
		glRotatef(angle3a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle3a, 0, 0, 1);

		glRotatef(angle3b, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle3b, 0, 0, 1);
	}
	if (step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle3a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle3a, 0, 0, 1);

		glRotatef(angle3b, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle3b, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(85, 0, 0);
	glVertex3f(85, 85, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(85, 0, 0);
	glVertex3f(85, 85, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////4
	glPushMatrix();
	glTranslatef(130, 85, 0);
	if (step2 == 1)
	{

		glRotatef(angle4, 0, 0, 1);
		glRotatef(-flip2, 1, 0, 0);
		glRotatef(-angle4, 0, 0, 1);

	}
	if (step3 == 1)
	{

		glRotatef(angle4, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle4, 0, 0, 1);

	}
	if (step4 == 1)
	{
		glRotatef(angle4, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle4, 0, 0, 1);
	}
	if (step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle4, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle4, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -85, 0);
	glVertex3f(85, -85, 0);
	glVertex3f(85, 0, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, -85, 0);
	glVertex3f(85, -85, 0);
	glVertex3f(85, 0, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////5
	glPushMatrix();
	glTranslatef(130, 190, 0);
	//////////////////////05 step3
	if (step3 == 1)
	{
		glRotatef(angle5a, 0, 0, 1);
		glRotatef(-flip3, 1, 0, 0);
		glRotatef(-angle5a, 0, 0, 1);
	}
	if (step4 == 1)
	{
		glRotatef(angle5a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle5a, 0, 0, 1);
	}
	if (step5 == 1)
	{
		glRotatef(angle5a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle5a, 0, 0, 1);

		glRotatef(angle5b, 0, 0, 1);
		glRotatef(-flip5, 1, 0, 0);
		glRotatef(-angle5b, 0, 0, 1);

	}
	if (step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle5a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle5a, 0, 0, 1);

		glRotatef(angle5b, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle5b, 0, 0, 1);
	}
	/////////////////
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 25, 0);
	glVertex3f(0, 25, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 25, 0);
	glVertex3f(0, 25, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////6
	glPushMatrix();
	glTranslatef(130, 190, 0);

	if (step5 == 1)
	{
		glRotatef(angle6, 0, 0, 1);
		glRotatef(-flip5, 1, 0, 0);
		glRotatef(-angle6, 0, 0, 1);
	}
	if (step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle6, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle6, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 25, 0);
	glVertex3f(-20, 25, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 25, 0);
	glVertex3f(-20, 25, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////  07  恆固定
	glPushMatrix();
	glTranslatef(130, 85, 0);

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 105, 0);
	glVertex3f(-20, 130, 0);
	glVertex3f(-130, 20, 0);
	glVertex3f(-105, 0, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 105, 0);
	glVertex3f(-20, 130, 0);
	glVertex3f(-130, 20, 0);
	glVertex3f(-105, 0, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////8
	glPushMatrix();
	glTranslatef(130, 85, 0);
	if (step4 == 1)
	{
		glRotatef(-flip4, 1, 0, 0);
	}
	if (step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(-180, 1, 0, 0);
	}

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-105, 0, 0);
	glVertex3f(-130, -20, 0);
	glVertex3f(-130, -60, 0);
	glVertex3f(-105, -85, 0);
	glVertex3f(-85, -85, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-105, 0, 0);
	glVertex3f(-130, -20, 0);
	glVertex3f(-130, -60, 0);
	glVertex3f(-105, -85, 0);
	glVertex3f(-85, -85, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////9
	glPushMatrix();

	glTranslatef(130, 85, 0);
	if (step2 == 1)
	{

		glRotatef(angle9a, 0, 0, 1);
		glRotatef(-flip2, 1, 0, 0);
		glRotatef(-angle9a, 0, 0, 1);
	}
	if (step3 == 1)
	{

		glRotatef(angle9a, 0, 0, 1);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle9a, 0, 0, 1);

	}
	if (step4 == 1)
	{
		/////////////////////////////////////////
		glRotatef(angle9a, 0, 0, 1);//保step3
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle9a, 0, 0, 1);
		//////////////////////////////////////
		glRotatef(angle9b, 0, 0, 1);
		glRotatef(-flip4, 0, 1, 0);
		glRotatef(-angle9b, 0, 0, 1);

	}
	if (step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		/////////////////////////////////////////
		glRotatef(angle9a, 0, 0, 1);//保step3
		glRotatef(-180, 1, 0, 0);
		glRotatef(-angle9a, 0, 0, 1);
		//////////////////////////////////////
		glRotatef(angle9b, 0, 0, 1);
		glRotatef(-180, 0, 1, 0);
		glRotatef(-angle9b, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-85, -85, 0);
	glVertex3f(0, -85, 0);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-85, -85, 0);
	glVertex3f(0, -85, 0);
	glEnd();
	glPopMatrix();
	//////////////////////////////////////////////////  10
	glPushMatrix();
	glTranslatef(0, 105, 0);
	///////////////////////////  10 step1
	if (step1 == 1)
	{

		glRotatef(angle10, 0, 0, 1);
		glRotatef(flip1, 1, 0, 0);
		glRotatef(-angle10, 0, 0, 1);

	}
	//////////////////////////////////////////////////
	if (step2 == 1 || step3 == 1 || step4 == 1 || step5 == 1 || step6 == 1 || step7 == 1 || step8 == 1)
	{
		glRotatef(angle10, 0, 0, 1);
		glRotatef(180, 1, 0, 0);
		glRotatef(-angle10, 0, 0, 1);
	}

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(110, 110, 0);
	glVertex3f(0, 110, 0);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(110, 110, 0);
	glVertex3f(0, 110, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////11
	glPushMatrix();
	glTranslatef(25, 85, 0);
	if (step6 == 1)
	{
		glRotatef(angle11, 0, 0, 1);
		glRotatef(flip6, 1, 0, 0);
		glRotatef(-angle11, 0, 0, 1);
	}
	if (step7 == 1 || step8 == 1)
	{
		glRotatef(angle11, 0, 0, 1);
		glRotatef(180, 1, 0, 0);
		glRotatef(-angle11, 0, 0, 1);
	}
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-25, 20, 0);
	glVertex3f(-25, 0, 0);
	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-25, 20, 0);
	glVertex3f(-25, 0, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////12
	glPushMatrix();
	glTranslatef(25, 85, 0);

	if (step4 == 1)
	{
		glRotatef(-flip4, 1, 0, 0);
	}
	if (step5 == 1)
	{
		glRotatef(-180, 1, 0, 0);
	}
	if (step6 == 1)
	{
		glRotatef(-180, 1, 0, 0);

		glRotatef(angle12b, 0, 0, 1);
		glRotatef(flip6, 1, 0, 0);
		glRotatef(-angle12b, 0, 0, 1);
	}

	if (step7 == 1 || step8 == 1)
	{
		glRotatef(-180, 1, 0, 0);

		glRotatef(angle12b, 0, 0, 1);
		glRotatef(180, 1, 0, 0);
		glRotatef(-angle12b, 0, 0, 1);
	}

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(-25, 0, 0);
	glVertex3f(-25, -20, 0);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(linewidth);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-25, 0, 0);
	glVertex3f(-25, -20, 0);
	glEnd();
	glPopMatrix();
	/////////////////////////////////////////////////13
	//glTranslatef(25, 0, 0);
	glPushMatrix();
	if (step4 == 1)
	{
		glTranslatef(25, offset1, 0);
		glRotatef(-flip4, 1, 0, 0);
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 - offset1, 0);
		glVertex3f(-25, -offset1 + 25, 0);
		glVertex3f(-25, -offset1, 0);

		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0 - offset1, 0);
		glVertex3f(-25, -offset1 + 25, 0);
		glVertex3f(-25, -offset1, 0);
		glEnd();
	}
	if (step5 == 1 || step6 == 1 || step7 == 1)
	{
		glTranslatef(25, offset1, 0);
		glRotatef(-180, 1, 0, 0);
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0 - offset1, 0);
		glVertex3f(-25, -offset1 + 25, 0);
		glVertex3f(-25, -offset1, 0);

		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0 - offset1, 0);
		glVertex3f(-25, -offset1 + 25, 0);
		glVertex3f(-25, -offset1, 0);
		glEnd();

	}
	if (step8 == 1)
	{
		glTranslatef(0, 85 * 2 - 25, 0);
		glRotatef(-45, 0, 0, 1);
		glRotatef(flip8, 0, 1, 0);
		glRotatef(45, 0, 0, 1);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);

		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(25, 25, 0);
		glVertex3f(0, 25, 0);
		glEnd();

	}
	if (step1 == 1 || step2 == 1 || step3 == 1)
	{
		glTranslatef(25, 0, 0);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(-25, 25, 0);
		glVertex3f(-25, 0, 0);

		glEnd();

		glColor3f(1, 1, 1);
		glLineWidth(linewidth);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(-25, 25, 0);
		glVertex3f(-25, 0, 0);
		glEnd();
	}
	glPopMatrix();
	/////////////////////////////////////////////////

	glPopMatrix();
	glutSwapBuffers();
}
void SetupRC()
{
	//glClearColor(1, 0.75f, 0.7929f, 1.0f);
	glClearColor(0, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}
void mySpecialKeys(unsigned char key, int x, int y)
{
	if (key == 13)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		xRot = 0.0f;
		yRot = 0.0f;
		zRot = 0.0f;
		fxRot = 0.0f;
		fyRot = 0.0f;
		flip = 0.0f;
		flip1 = 0.0f;
		flip2 = 0.0f;
		flip3 = 0.0f;
		flip4 = 0.0f;
		flip5 = 0.0f;
		flip6 = 0.0f;
		flip7 = 0.0f;
		flip8 = 0.0f;
		linewidth = 10;
		totalangle = 0;
		step1 = 1;
		step2 = 0;
		step3 = 0;
		step4 = 0;
		step5 = 0;
		step6 = 0;
		step7 = 0;
		step8 = 0;
		finish = 0;
	}
	if (key == 'w')
		xRot -= 5.0f;

	if (key == 's')
		xRot += 5.0f;

	if (key == 'a')
		yRot -= 5.0f;

	if (key == 'd')
		yRot += 5.0f;
	if (key == 'c')
		zRot -= 5.0f;

	if (key == 'z')
		zRot += 5.0f;


	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	if (key > 356.0f)
		zRot = 0.0f;

	if (key < -1.0f)
		zRot = 355.0f;
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y)
{

	if (key == GLUT_KEY_LEFT)
	{
		flip += 3.0f;
		totalangle = flip;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		flip += 3.0f;
		totalangle = flip;
	}
	if (totalangle <= 180 && totalangle >= 0)
	{
		step1 = 1;
		flip1 = flip;
	}

	if (totalangle >= 181 && totalangle <= 180 * 2)
	{
		step1 = 0;
		step2 = 1;
		flip2 = flip - 180 * 1;

	}

	if (totalangle >= 180 * 2 + 1 && totalangle <= 180 * 3)
	{
		step2 = 0;
		step3 = 1;
		flip3 = flip - 180 * 2;

	}
	if (totalangle >= 180 * 3 + 1 && totalangle <= 180 * 4)
	{
		step3 = 0;
		step4 = 1;
		flip4 = flip - 180 * 3;

	}
	if (totalangle >= 180 * 4 + 1 && totalangle <= 180 * 5)
	{
		step4 = 0;
		step5 = 1;
		flip5 = flip - 180 * 4;

	}
	if (totalangle>180 * 5 && totalangle <= 180 * 6)
	{
		step5 = 0;
		step6 = 1;
		flip6 = flip - 180 * 5;

	}
	if (totalangle>180 * 6 && totalangle <= 180 * 7)
	{
		step6 = 0;
		step7 = 1;
		flip7 = flip - 180 * 6;

	}
	if (totalangle>180 * 7 && totalangle <= 180 * 8)
	{
		step7 = 0;
		step8 = 1;
		flip8 = flip - 180 * 7;
	}
	if (totalangle >= 180 * 8)
	{
		finish = 1;
	}
	/////////////////////////////// Refresh the Window
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -400.0f);
}
int _tmain(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 800);
	glutCreateWindow("E14031083 Heart Origami");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(mySpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	cout << angle2 << endl;
	glutMainLoop();
	return 0;
}