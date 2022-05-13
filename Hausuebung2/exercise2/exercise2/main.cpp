/*
Programm that demonstrates light sources in OpenGL
by Roman Kofler-Hofer, 24.04.20222
*/

#include "GL/freeglut.h"
#include "math.h"
#include <iostream>

using namespace std;
int windowid;

/*~~~~~~~~~~~~~~~~~~GLOBAL VARIABLES~~~~~~~~~~~~~~~~~~*/

// Camera variables
GLfloat eye_x = 5.f, eye_y = 4.f, eye_z = 23.0f;
GLfloat center_x = 5.f, center_y = 0.f, center_z = 0.f;

//parameter for directional light
GLfloat directional_light_dir[] = {1.0f, 1.0f, -1.0f, 0.0f };

//parameters for point light
GLfloat pointLight_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat pointLight_pos[] = {5.0f, 3.0f, 5.0f, 1.0f };

//parameters for spot light
GLfloat spotLight_color2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat spotLight_pos2[] = { 5.0f, 2.0f, 7.0f, 1.0f };
GLfloat spotLight_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f};

//parameters for additional spot light
GLfloat light_color[] = {1.0f, 0.3f, 0.1f, 1.0f};
GLfloat light_pos[] = {5.0f, 0.0f, 4.0f, 1.0f};
GLfloat light_direction[] = {-1.0f, 0.0f, -1.0f, 1.0f };

//parameter for ambient light
GLfloat lmodel_ambient[] = { 0.7f, 0.1f, 0.3f, 1.0f };

// Material attributes
//Material 0
GLfloat mat0_ambient[] = { 0.7f, 0.2f, 0.5f, 1.0f };
GLfloat mat0_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat mat0_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat0_shininess = 50.0f;
GLfloat mat0_emmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Material 1
GLfloat mat1_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat1_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat mat1_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat1_shininess = 0.0f;
GLfloat mat1_emmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Material 2
GLfloat mat2_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat mat2_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat2_specular[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat mat2_shininess = 70.0f;
GLfloat mat2_emmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Material 3
GLfloat mat3_ambient[] = { 0.3f, 0.5f, 0.0f, 1.0f };
GLfloat mat3_diffuse[] = { 0.3f, 0.5f, 0.7f, 1.0f };
GLfloat mat3_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat3_shininess = 100.0f;
GLfloat mat3_emmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Material 4
GLfloat mat4_ambient[] = { 0.3f, 0.6f, 0.8f, 1.0f };
GLfloat mat4_diffuse[] = { 0.2f, 0.5f, 0.8f, 1.0f };
GLfloat mat4_specular[] = { 0.5f, 0.0f, 0.0f, 1.0f };
GLfloat mat4_shininess = 50.0f;
GLfloat mat4_emmission[] = { 0.0f, 0.2f, 0.4f, 1.0f };

//Material 5
GLfloat mat5_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat5_diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };
GLfloat mat5_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat5_shininess = 20.0f;
GLfloat mat5_emmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//Material Room
GLfloat matRoom_ambient[] = { 0.2f, 0.4f, 0.7f, 1.0f };
GLfloat matRoom_diffuse[] = { 0.5f, 0.3f, 0.5f, 1.0f };
GLfloat matRoom_specular[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat matRoom_shininess = 80.0f;
GLfloat matRoom_emmission[] = { 0.0f, 0.5f, 0.3f, 0.0f };

//global variables for animation
GLfloat attenuation_pointLight = 0.0f;
GLfloat attenuation_spotLight = 0.0f;
GLfloat discoBallRotation = 0.0f;

GLfloat yRotationDirectionalLight = 0;
GLfloat angleDirectional = 0.0f; // angle of rotation for the directional light direction
GLfloat angleSpot = 0.0f; // angle of rotation for the spotlight direction
GLfloat lxSpot = 0.0f, lzSpot = -1.0f; // actual vector components representing the spotlight direction

//control board global variables (for position of switches etc.)
GLfloat attenuation_spotLight_control_rotation = 0.0f;
GLfloat attenuation_pointLight_control_rotation = 0.0f;
bool directionalLightOn = true;
bool pointLightOn = true;
bool spotLightOn = true;
bool fogEnabled = false;

//needed for attenuation and 
GLfloat delta_attenuation = 0.05f;
GLfloat statesOfAttenuationControls = (1.0 / delta_attenuation);	//in my case 20 steps (from 0 to 1.0 with 0.05 steps)
GLfloat degreesPerKeyPress = 360 / statesOfAttenuationControls;	// 360 / 20 = 18 degrees rotation with each key press

//animation of persons
GLfloat figure1_x = 1.0f;
bool figure1_goingRight = true;

GLfloat figure2_x = 3.0f;
bool figure2_goingRight = false;

GLfloat figure3_x = 5.0f;
bool figure3_goingRight = false;

GLfloat figure4_x = 6.0f;
bool figure4_goingRight = false;

GLfloat figure5_x = 8.0f;
bool figure5_goingRight = true;

/*~~~~~~~~~~~~~~~~~~GLOBAL VARIABLES END~~~~~~~~~~~~~~~~~~*/

/* This function should be called when the window is resized. It has to be
   registered as a callback in glutReshapeFunc. The function sets up the
   correct perspective projection. Don't worry about it we will not go into
   detail but we need it for correct perspective 3D rendering. */
void reshapeFunc(int xwidth, int yheight) {
  if (yheight == 0 || xwidth == 0) return;  // Nothing is visible, return

  glMatrixMode(GL_PROJECTION); // Set a new projection matrix
  glLoadIdentity();
  // Angle of view: 40 degrees
  // Near clipping plane distance: 0.5
  // Far clipping plane distance: 20.0
  gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 30.0f);
  glViewport(0, 0, xwidth, yheight);  // Use the whole window for rendering
}

/*
Task 1.1 - enables a directional light source (using global variables)
In: void
Out: void
*/
void enableDirectionalLight () {
	glLightfv(GL_LIGHT0, GL_POSITION, directional_light_dir);
  glEnable(GL_LIGHT0);
}

/*
Task 1.1 - enables a point light source (using global variables)
In: void
Out: void
*/
void enablePointLight () {
  glLoadIdentity();
  glLightfv(GL_LIGHT1, GL_DIFFUSE, pointLight_color);
  glLightfv(GL_LIGHT1, GL_POSITION, pointLight_pos);
  glEnable(GL_LIGHT1);
}

/*
Task 1.1 - enables a spot light source (using global variables)
In: void
Out: void
*/
void enableSpotLight () {
	glLoadIdentity();
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLight_direction);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, spotLight_color2);
  glLightfv(GL_LIGHT2, GL_POSITION, spotLight_pos2);
  glEnable(GL_LIGHT2);
}

/*
Not related to a particular task.
One aditional spotlight was implemented for nicer looks.This light is not being animated.
*/
void enableSpotLight3() {
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 270.f);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos);
	glEnable(GL_LIGHT3);
}

/*
Task 1.2
Materials are set using global variables.
All methods set an ambient, diffuse, specular, shininess and emmission. 
	Some of these might be set to 0 (depending on the desired material look)
These materials are applied to figures and other surfaces

Input (for all material fucntions): void
Ouput (for all material functions): void
*/
void materialZero(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat0_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat0_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat0_emmission);
}

void materialOne(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat1_emmission);
}

void materialTwo(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat2_emmission);
}

void materialThree(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat3_emmission);
}

void materialFour(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat4_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat4_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat4_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat4_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat4_emmission);
}

void materialFive(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat5_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat5_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat5_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mat5_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, mat5_emmission);
}

void materialRoom(void) {
  glMaterialfv(GL_FRONT, GL_AMBIENT, matRoom_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matRoom_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matRoom_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, matRoom_shininess);
  glMaterialfv(GL_FRONT, GL_EMISSION, matRoom_emmission);
}

/*
Task 1.3 - enables ambient light (using global variables)
In: void
Out: void
*/
void enableAmbientLight(void){
  glLoadIdentity();
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}

/*
(Main) task 1 (draw scene)
This function draws the "surrounding" or room in which the dance floor will be positioned
In: void
Out: void
*/
void drawDiscoRoom (void) {
	materialRoom();
	enableSpotLight3();
	glPushMatrix();
		glBegin(GL_QUADS);
			//background
			glVertex3f(-3.0f,6.0f,0);
			glVertex3f(-3.0f,-1.0f,0);
			glVertex3f(13.0f,-1.0f,0);
			glVertex3f(13.0f,6.0f,0);

			//top of cube
			glVertex3f(-3.0f,6.0f,0);
			glVertex3f(-3.0f,6.0f,13.0f);
			glVertex3f(13.0f, 6.0f, 13.0f);
			glVertex3f(13.0f,6.0f,0);

			//bottom
			glVertex3f(-3.0f, -1.0f, 0);
			glVertex3f(-3.0f, -1.0f, 15.0f);
			glVertex3f(13.0f, -1.0f, 15.0f);
			glVertex3f(13.0f, -1.0f, 0);

			//left
			glVertex3f(-3.0f,-1.0f,0);
			glVertex3f(-3.0f,6.0f,0);
			glVertex3f(-3.0f,6.0f,15.0f);
			glVertex3f(-3.0f,-1.0f,15.0f);

			//right
			glVertex3f(13.0f,-1.0f,0);
			glVertex3f(13.0f,6.0f,0);
			glVertex3f(13.0f,6.0f,15.0f);
			glVertex3f(13.0f,-1.0f,15.0f);
		glEnd();
	glPopMatrix();
}

/*
(Main) task 1 (draw scene)
This function draws the dance floor on which the "people" will be positioned
In: void
Out: void
*/
void drawDanceFloor (void) {
	materialZero();
	glPushMatrix();
			glBegin(GL_QUADS);
				//top of cube
				glVertex3f(0,0,0);
				glVertex3f(0,0,10.0f);
				glVertex3f(10.0f, 0, 10.0f);
				glVertex3f(10.0f,0,0);

				//bottom
				glVertex3f(0, -1.0f, 0);
				glVertex3f(0, -1.0f, 10.0f);
				glVertex3f(10.0f, -1.0f, 10.0f);
				glVertex3f(10.0f, -1.0f, 0);

				//back
				glVertex3f(0,0,0);
				glVertex3f(0,-1.0f,0);
				glVertex3f(10.0f,-1.0f,0);
				glVertex3f(10.0f,0,0);

				//front
				glVertex3f(0,0,10.0f);
				glVertex3f(0,-1.0f,10.0f);
				glVertex3f(10.0f,-1.0f,10.0f);
				glVertex3f(10.0f,0,10.0f);

				//left
				glVertex3f(0,-1.0f,0);
				glVertex3f(0,0,0);
				glVertex3f(0,0,10.0f);
				glVertex3f(0,-1.0f,10.0f);

				//right
				glVertex3f(10.0f,-1.0f,10.0f);
				glVertex3f(10.0f,-1.0f,0);
				glVertex3f(10.0f,0,0);
				glVertex3f(10.0f,0,10.0f);
				
			glEnd();
		glPopMatrix();
}

/*
(Main) task 1 (draw scene)
This function draws one person that will be positioned on the dance floor
The person consists of a cone as body and a sphere as head
In: x, y and z coordinates of start position of person
Out: void
*/
void drawPerson (float xPos, float yPos, float zPos) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.3f,0.8f,20,20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(xPos, yPos+0.7f, zPos);
		glutSolidSphere(0.2,20,10);
	glPopMatrix();
}

/*
(Main) task 1 (draw scene)
This function calls "drawPerson" five times with 5 different starting positions and materials.
Thus the persons are placed on the dance floor
In: void
Out: void
*/
void drawPersons (void) {
	materialOne();
	drawPerson(figure1_x, 0.0f, 8.0f);

	materialTwo();
	drawPerson(figure2_x, 0.0f, 2.5f);

	materialThree();
	drawPerson(figure3_x, 0.0f, 5.0f);

	materialFour();
	drawPerson(figure4_x, 0.0f, 7.0f);

	materialFive();
	drawPerson(figure5_x, 0.0f, 9.0f);
}

/*
Task 2
The the following functions allow to disable the the lights (directional-, point-, spot- light)
In: void
Out: void
*/
void disableDirectionalLight (void) {
	glDisable(GL_LIGHT0);
}

void disablePointLight (void) {
	glDisable(GL_LIGHT1);
}

void disableSpotLight (void) {
	glDisable(GL_LIGHT2);
}

/*
Taks 2.1. attenuation -> see keyboard function
*/

/*
Task 2.2.
This function draws a "box" which should represent the control board.
Later on switches and controlls will be drawn on top of this box
In: void
Out: void
*/
void drawcontrolBoardBase (void) {
glPushMatrix();
			glTranslatef(3.25f, -0.05f, 12.5f);
			glScalef(0.7f, 0.7f, 1.0f);
			glBegin(GL_QUADS);
				materialFour();
				//top of cube
				glVertex3f(0,0,0);
				glVertex3f(0,0,2.0f);
				glVertex3f(5.0f, 0, 2.0f);
				glVertex3f(5.0f,0,0);

				materialFive();
				//bottom
				glVertex3f(0, -2.0f, 0);
				glVertex3f(0, -2.0f, 2.0f);
				glVertex3f(5.0f, -2.0f, 2.0f);
				glVertex3f(5.0f, -2.0f, 0);

				//back
				glVertex3f(0,0,0);
				glVertex3f(0,-2.0f,0);
				glVertex3f(5.0f,-2.0f,0);
				glVertex3f(5.0f,0,0);

				//front
				glVertex3f(0,0,2.0f);
				glVertex3f(0,-2.0f,2.0f);
				glVertex3f(5.0f,-2.0f,2.0f);
				glVertex3f(5.0f,0,2.0f);

				//left
				glVertex3f(0,-2.0f,0);
				glVertex3f(0,0,0);
				glVertex3f(0,0,2.0f);
				glVertex3f(0,-2.0f,2.0f);

				//right
				glVertex3f(5.0f,-2.0f,2.0f);
				glVertex3f(5.0f,-2.0f,0);
				glVertex3f(5.0f,0,0);
				glVertex3f(5.0f,0,2.0f);
			glEnd();
		glPopMatrix();
}

/*
Task 2.2.
With this function a horizontal switch/control can be drawn. 
The switch consits of a horizontal line and a cube that represents the switch. Ít should look something like this: --|---
In: x, y and z position of the switch; switchStatus = status if switch is currently on or off.
    Depending on switch status an offset to the y-coordinate will be added.
Out: void
*/
void drawHorizontalControl (GLfloat xPos, GLfloat yPos, GLfloat zPos, bool switchStatus) {
		GLfloat onOffOffset = 0.0f;

		if(switchStatus) {
			onOffOffset = 0.3f;
		}
		
		//background horizontal line
		materialZero();
		glPushMatrix();
			glTranslatef(xPos, yPos, zPos);
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0.0f ,0, 0.1f);
				glVertex3f(0.7f, 0.0f, 0.1f);
				glVertex3f(0.7f, 0.0f, 0);
			glEnd();
		glPopMatrix();

		//switch itself
		materialOne();
		glPushMatrix();
			glTranslatef(xPos+0.2+onOffOffset, yPos, zPos);
			glutSolidCube(0.2f);
		glPopMatrix();
}

/*
Task 2.2.
This function draws the 4 switches needed on my control board.
One switch for the directional light, point light, spot light and one for the fog on/off switch
In: void
Out: void
*/
void drawLightAndFogControls (void) {
		drawHorizontalControl(3.5f, 0, 13.1f, directionalLightOn);
		drawHorizontalControl(4.5f, 0, 13.1f, pointLightOn);
		drawHorizontalControl(5.5f, 0, 13.1f, spotLightOn);
		drawHorizontalControl(3.5f, 0, 13.9f, fogEnabled);
}

/*
Task 2.2.
This function draws an "arrow-control" consisting of thin cylinder and an triangle that is positioned on top of the cylinder
In: x, y and z position of the item; rotation = rotation angle of triangel.
Out: void
*/
void drawTriangleControl (GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat rotation) {
	
	//cylinder on which triangle is positioned
	materialThree();
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90, 1.0f, 0, 0);
		glutSolidCylinder(0.2f, 0.1f, 50, 30);
	glPopMatrix();


	//arrows
	materialOne();
	glPushMatrix();
		glTranslatef(xPos, yPos+0.01f, zPos);
		glScalef(0.7f, 0.7f, 0.7f);
		glRotatef(-90, 1.0f, 0, 0);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, 0.2f, 0.0f);
		glEnd();
	glPopMatrix();
}

/*
Task 2.2.
draws to triangle controls. One for the point light attenuation and one for the spot light attenuation
In: void
Out: void
*/
void drawAttenuationControls () {
		drawTriangleControl(4.7f, 0.0f, 13.9f, attenuation_pointLight_control_rotation);
		drawTriangleControl(5.3f, 0.0f, 13.9f, attenuation_spotLight_control_rotation);
}

/*
Task 2.2.
Draws the whole control board (so the base box, the light and fog controls and the controls for the attenuation)
In: void
Out: void
*/
void drawControlBoard (void) {
		drawcontrolBoardBase();
		drawLightAndFogControls();
		drawAttenuationControls();
}

/*
Task 3
This function enables the fog.
Same as in exervice. Just changed color, start/end
In: void
Out: void
*/
void enableFog() {
  GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR }; 
  GLuint fogfilter = 2;                              
  GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };  

  glFogi(GL_FOG_MODE, fogMode[fogfilter]);  
  glFogfv(GL_FOG_COLOR, fogColor);          
  glFogf(GL_FOG_DENSITY, 0.30f);            
  glHint(GL_FOG_HINT, GL_DONT_CARE);        
  glFogf(GL_FOG_START, 0.0f);               
  glFogf(GL_FOG_END, 38.0f);                
  glEnable(GL_FOG);                         
};

/*
Task 3
Allows to disable fog again
In: void
Out: void
*/
void disableFog () {
	glDisable(GL_FOG);
}

/*
Task 3
Adds a disco ball to the scene
In: void
Out: void
*/
void drawDiscoBall (void) {
  materialFour();
	glShadeModel(GL_FLAT);		//for disco ball effect
  glPushMatrix();
    glTranslatef(5.0f, 4.0f, 5.0f);
		glRotatef(discoBallRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidSphere(1.0f, 20, 20);
  glPopMatrix();
}

/*
Task 3.1.
With every call of this function the x and z direction of the spot light slightly changes resulting in an animation effect of this light source
Function will be called in a glutTimerFunc function
In: void
Out: void
*/
void rotateSpot(void) {
  angleSpot -= 0.03f;
  lxSpot = sin(angleSpot);
  lzSpot = -cos(angleSpot);
	
	spotLight_direction[0] = lxSpot;
	spotLight_direction[2] = lzSpot;
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotLight_direction);
}

/*
Task 3.1.
With every call of this function the y direction of the directional light slightly changes resulting in an animation effect of this light source
Function will be called in a glutTimerFunc function
In: void
Out: void
*/
void rotateDirectionalLight () {
	angleDirectional -= 0.03f;
	yRotationDirectionalLight = -cos(angleDirectional);
	directional_light_dir[1] = yRotationDirectionalLight;
	glLightfv(GL_LIGHT0, GL_POSITION, directional_light_dir);
}


/*
This method moves a figure along the x axis. Depending on the position the figure will be moved to the left or to the right.
Global variables are used and manipulated by this function
In: - currentXPos = the current position of the person on the x axis
    - currentlyGoingRight = info if person was previously moved to the right or not
		- speed = offset / speed with which a person is moved along the x axis
Out: void
*/
void moveAlongXAxis (GLfloat &currentXPos, bool &currentlyGoingRight, GLfloat speed) {
	
	//check if next position is still within boundaries. If yes, move figure
	if((currentlyGoingRight == true) && ((currentXPos + speed) < 10.1f)) {
		currentXPos += speed;
	}
	else if((currentlyGoingRight == false) && ((currentXPos - speed) > 0.0f)) {
		currentXPos -= speed;
	}
	
	//changing direction
	if(currentXPos >= 10.0f) {
		currentlyGoingRight = false;
	}
	else if(currentXPos <= 0.2f) {
		currentlyGoingRight = true;
	}
}

/*
Function that rotates the disco ball
In: void
Out: void
*/
void animateDiscoBall (void) {
	discoBallRotation += 0.4;
}

/*
Function that is used in the glutTimerFunc function.
It is responsible for animating the scene.
So all relevant functions are called (moving figures along x axis, animating disco ball, rotation of lights)
*/
void animateScene (int id) {
	moveAlongXAxis(figure1_x, figure1_goingRight, 0.02f);
	moveAlongXAxis(figure2_x, figure2_goingRight, 0.03f);
	moveAlongXAxis(figure3_x, figure3_goingRight, 0.025f);
	moveAlongXAxis(figure4_x, figure4_goingRight, 0.015f);
	moveAlongXAxis(figure5_x, figure5_goingRight, 0.01f);
	animateDiscoBall();
	rotateSpot();
	rotateDirectionalLight();
	glutPostRedisplay();
	glutTimerFunc(10, animateScene, 0);
}


/* 
The keyboard is used to change the attenuation of the spot and point light
Moreover it is used for switching on/off light sources and the fog.
*/
void keyboard(unsigned char key, int xcoor, int ycoor) {
	float delta = 0.5f;
	switch (key) {
    case 27: // escape key
      glutDestroyWindow(windowid);
      exit(0);
      break;
		case '+':
		if(attenuation_pointLight + delta_attenuation <= 1.0) {
				attenuation_pointLight += delta_attenuation;
				attenuation_pointLight_control_rotation -= degreesPerKeyPress;					//- because it should rotate clockwise when increasing attenuation
				glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, attenuation_pointLight);
			}
			break;
		case '-':
			if(attenuation_pointLight - delta_attenuation > 0.0f) {
				attenuation_pointLight -= delta_attenuation;
				attenuation_pointLight_control_rotation += degreesPerKeyPress;				//+ because it should rotate anti-clockwise when decreasing attenuation
				glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, attenuation_pointLight);
			}
			break;
		case '.':
			if(attenuation_spotLight + delta_attenuation <= 1.0) {
				attenuation_spotLight += delta_attenuation;
				attenuation_spotLight_control_rotation -= degreesPerKeyPress;					//- because it should rotate clockwise when increasing attenuation
				glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, attenuation_spotLight);
			}
			break;
		case ',':
			if(attenuation_spotLight - delta_attenuation > 0.0f) {
				attenuation_spotLight -= delta_attenuation;
				attenuation_spotLight_control_rotation += degreesPerKeyPress;				//+ because it should rotate anti-clockwise when decreasing attenuation
				glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, attenuation_spotLight);	
			}
			break;
		case 'h':
			disableDirectionalLight();
			directionalLightOn = false;
			break;
		case 'z':
			enableDirectionalLight();
			directionalLightOn = true;
			break;
		case 'j':
			disablePointLight();
			pointLightOn = false;
			break;
		case 'u':
			enablePointLight();
			pointLightOn = true;
			break;
		case 'k':
			disableSpotLight();
			spotLightOn = false;
			break;
		case 'i':
			enableSpotLight();
			spotLightOn = true;
			break;
		case 'f':
			if(fogEnabled) {
				disableFog();
				fogEnabled = false;
			}
			else {
				enableFog();
				fogEnabled = true;
			}
  }

  glutPostRedisplay();
}

/*
calls all functions for drawing persons, disco and other items
provides light sources
In: void
Out: void
*/
void renderScene(void) {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0); // original black

	glLoadIdentity();
	gluLookAt (						
			eye_x, eye_y, eye_z,
			center_x, center_y, center_z,
			0.f, 1.f, 0.f
	);

	drawDanceFloor();
	drawDiscoRoom();
	drawControlBoard();
	drawDiscoBall();
	drawPersons();

	glutSwapBuffers();
}

/*
main loop, callbacks are registered
*/
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(500, 200);
  glutInitWindowSize(800, 600); 
  windowid = glutCreateWindow("Disco room"); 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

	enableAmbientLight();
	enableDirectionalLight();
  enablePointLight();
	enableSpotLight();

  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshapeFunc);
  glutDisplayFunc(renderScene);
	glutTimerFunc(10, animateScene, 0);

  glutMainLoop();
  return 0;
}