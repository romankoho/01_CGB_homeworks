#include "GL/freeglut.h"
#include "math.h"
#include <iostream>

using namespace std;
int windowid;

// Camera motion variables
GLfloat eye_x = 5.f, eye_y = 3.f, eye_z = 20.f;
GLfloat center_x = 5.f, center_y = 0.f, center_z = 0.f;

GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f };
GLfloat directional_light_dir[] = {1.0f, 1.0f, -1.0f, 0.0f };

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


GLfloat mat_shininess_init[] = { 0.0f };
GLfloat shininess_init = 0.0f;
GLfloat mat_specular_init[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//control board global variables (for position of switches etc.)
GLfloat directionalLight_yTrans = 0.0f;
GLfloat pointLightSwitch_yTrans = 0.0f;
GLfloat spotLightSwitch_yTrans = 0.0f;
GLfloat fog_switch_xTranslate = 0.0f;
GLfloat attenuation_spotLight_control_rotation = 0.0f;
GLfloat attenuation_pointLight_control_rotation = 0.0f;

//global variables for animation
GLfloat attenuation_pointLight = 0.0f;
GLfloat attenuation_spotLight = 0.0f;

GLfloat discoBallRotation = 0.0f;

GLfloat angle = 0.0f; // angle of rotation for the spotlight direction
GLfloat lx = 0.0f, lz = -1.0f; // actual vector components representing
                               // the spotlight direction

bool fogEnabled = false;

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

//Task 1.1 -> directional light
void enableDirectionalLight () {
	glLightfv(GL_LIGHT0, GL_POSITION, directional_light_dir);
  glEnable(GL_LIGHT0);
}

void disableDirectionalLight () {
	glDisable(GL_LIGHT0);
}

//Task 1.1 -> point light
void enablePointLight () {
  glLoadIdentity();
  GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat light_pos[] = {5.0f, 3.0f, 5.0f, 1.0f };
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
  glEnable(GL_LIGHT1);
}

void disablePointLight () {
	glDisable(GL_LIGHT1);
}

//Task 1.1. -> spot light
void enableSpotLight () {
	glLoadIdentity();
  GLfloat light_color2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
  GLfloat light_pos2[] = { 5.0f, 2.0f, 13.0f, 1.0f };
  GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f, 1.0f };
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);
  glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
  glEnable(GL_LIGHT2);
}

void disableSpotLight () {
	glDisable(GL_LIGHT2);
}

void enableAmbientLight(void){
  glLoadIdentity();
	//Task 1.3 -> ambientLight
	GLfloat lmodel_ambient[] = { 0.7f, 0.1f, 0.3f, 1.0f };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  
	glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void drawDanceFloor (void) {
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

void drawPerson (float xPos, float yPos, float zPos) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCylinder(0.3f, 0.8f, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(xPos, yPos+0.15f, zPos);
		glutSolidSphere(0.2,20,10);
	glPopMatrix();
}

void controlDeskBackground () {
	//Background
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3f(6.0f, 2.5f, 7.0f);
			glVertex3f(10.0f, 2.5f, 7.0f);
			glVertex3f(10.0f, 5.0f, 7.0f);
			glVertex3f(6.0f, 5.0f, 7.0f);
		glEnd();
	glPopMatrix();	
}

//vertical "middle lines" of light switches
void controlDeskMiddelLinesLightSwitches() {
	materialZero();
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3f(6.9f, 4.0f, 7.01f);
			glVertex3f(7.0f, 4.0f, 7.01f);
			glVertex3f(7.0f, 4.6f, 7.01f);
			glVertex3f(6.9f, 4.6f, 7.01f);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(7.9f, 4.0f, 7.01f);
			glVertex3f(8.0f, 4.0f, 7.01f);
			glVertex3f(8.0f, 4.6f, 7.01f);
			glVertex3f(7.9f, 4.6f, 7.01f);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(8.9f, 4.0f, 7.01f);
			glVertex3f(9.0f, 4.0f, 7.01f);
			glVertex3f(9.0f, 4.6f, 7.01f);
			glVertex3f(8.9f, 4.6f, 7.01f);
		glEnd();
	glPopMatrix();
}

//light on/off switches
void lightSwitches() {
	materialFive();
	//switch for directional light
	glPushMatrix();
		glTranslatef(0.0f, directionalLight_yTrans, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(6.7f, 4.45f, 7.02f);
			glVertex3f(7.2f, 4.45f, 7.02f);
			glVertex3f(7.2f, 4.35f, 7.02f);
			glVertex3f(6.7f, 4.35f, 7.02f);
		glEnd();
	glPopMatrix();

	//switch for point light
	glPushMatrix();
		glTranslatef(0.0f, pointLightSwitch_yTrans, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(7.7f, 4.45f, 7.02f);
			glVertex3f(8.2f, 4.45f, 7.02f);
			glVertex3f(8.2f, 4.35f, 7.02f);
			glVertex3f(7.7f, 4.35f, 7.02f);
		glEnd();
	glPopMatrix();

	//switch for spotlight
	glPushMatrix();
	glTranslatef(0.0f, spotLightSwitch_yTrans, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(8.7f, 4.45f, 7.02f);
			glVertex3f(9.2f, 4.45f, 7.02f);
			glVertex3f(9.2f, 4.35f, 7.02f);
			glVertex3f(8.7f, 4.35f, 7.02f);
		glEnd();
	glPopMatrix();
}

void attenuationControls () {
	materialFive();
	//control for attenuation of point light
	glPushMatrix();
		glTranslatef(7.0f, 3.3f, 7.01f);
		glRotatef(attenuation_spotLight_control_rotation, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, 0.2f, 0.0f);
		glEnd();
	glPopMatrix();

	//control for attenuation of spot light
	glPushMatrix();
		glTranslatef(8.0f, 3.3f, 7.01f);
		glRotatef(attenuation_pointLight_control_rotation, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(-0.1f, -0.2f, 0.0f);
			glVertex3f(0.1f, -0.2f, 0.0f);
			glVertex3f(0.0f, 0.2f, 0.0f);
		glEnd();
	glPopMatrix();
}

void fogControl () {

	//"middle line" for fog switch 
	materialZero();
	glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3f(8.6f, 3.2f, 7.01f);
			glVertex3f(9.3f, 3.2f, 7.01f);
			glVertex3f(9.3f, 3.3f, 7.01f);
			glVertex3f(8.6f, 3.3f, 7.01f);
		glEnd();
	glPopMatrix();

	//switch
	materialFive();
	glPushMatrix();
	glTranslatef(fog_switch_xTranslate, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(8.75f, 3.0f, 7.02f);
			glVertex3f(8.85f, 3.0f, 7.02f);
			glVertex3f(8.85f, 3.5f, 7.02f);
			glVertex3f(8.75f, 3.5f, 7.02f);
		glEnd();
	glPopMatrix();
}

void drawDiscoBall (void) {
  glShadeModel(GL_FLAT);
  glPushMatrix();
    glTranslatef(5.0f, 3.0f, 5.0f);
		glRotatef(discoBallRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidSphere(0.6f, 20, 20);
  glPopMatrix();
}

void enableFog() {
  GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR }; //  types of fog
  GLuint fogfilter = 2;                              // which fog to use
  GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };  // fog colour

  glFogi(GL_FOG_MODE, fogMode[fogfilter]);  // fog mode
  glFogfv(GL_FOG_COLOR, fogColor);          // set fog colour
  glFogf(GL_FOG_DENSITY, 0.30f);            // how dense will the fog be
  glHint(GL_FOG_HINT, GL_DONT_CARE);        // fog hint value
  glFogf(GL_FOG_START, 0.0f);               // fog start depth
  glFogf(GL_FOG_END, 38.0f);                 // fog end depth
  glEnable(GL_FOG);                         // enables GL_FOG
};

void disableFog () {
	glDisable(GL_FOG);
}

void rotateSpot(void) {
  angle -= 0.005f;
  lx = sin(angle);
  lz = -cos(angle);
	
	//spot_direction[0] = lx;
	spot_direction[2] = lz;
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
}

void rotateDirectionalLight () {
	angle -= 0.03f;
	GLfloat ly = -cos(angle);
	directional_light_dir[1] = ly;
	glLightfv(GL_LIGHT0, GL_POSITION, directional_light_dir);

}

void animateFigure (GLfloat &currentXPos, bool &currentlyGoingRight, GLfloat speed) {
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

void animateDiscoBall () {
	discoBallRotation += 0.4;
}

void animateFigures (int id) {
	animateFigure(figure1_x, figure1_goingRight, 0.03f);
	animateFigure(figure2_x, figure2_goingRight, 0.05f);
	animateFigure(figure3_x, figure3_goingRight, 0.04f);
	animateFigure(figure4_x, figure4_goingRight, 0.015f);
	animateFigure(figure5_x, figure5_goingRight, 0.01f);
	animateDiscoBall();
	rotateSpot();
	rotateDirectionalLight();
	glutPostRedisplay();

	glutTimerFunc(10, animateFigures, 0);
}

void renderScene(void) {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
  glClearColor(0.0, 0.0, 0.0, 0.0); // original black

	glLoadIdentity();
	gluLookAt (						
			eye_x, eye_y, eye_z,
			center_x, center_y, center_z,
			0.f, 1.f, 0.f
	);

	materialZero();
	drawDanceFloor();
	drawDiscoBall();

	materialFour();
	controlDeskBackground();
	controlDeskMiddelLinesLightSwitches();
	lightSwitches();
	attenuationControls();
	fogControl();

	materialOne();
	drawPerson(figure1_x, 0.8f, 8.0f);

	materialTwo();
	drawPerson(figure2_x, 0.8f, 2.5f);

	materialThree();
	drawPerson(figure3_x, 0.8f, 5.0f);

	materialFour();
	drawPerson(figure4_x, 0.8f, 7.0f);

	materialFive();
	drawPerson(figure5_x, 0.8f, 9.0f);

	glutSwapBuffers();
}


void keyboard(unsigned char key, int xcoor, int ycoor) {
  
	GLfloat delta_attenuation = 0.05f;
	GLfloat statesOfAttenuationControls = (1.0 / delta_attenuation);	//in my case 20 steps (from 0 to 1.0 with 0.05 steps)
	GLfloat degreesPerKeyPress = 360 / statesOfAttenuationControls;	// 360 / 20 = 18 degrees rotation with each key press

	float delta = 0.5f;
	switch (key) {
    case 'a': 
			eye_x -= delta;
			center_x  -= delta;
      break;
    case 'd':
			eye_x += delta;
			center_x  += delta;
      break;
    case 'w': 
			eye_z -= delta;
			center_z  -= delta;
      break;
    case 's':
			eye_z += delta;
			center_z  += delta;
      break;
	   case 'q': 
			eye_y += delta;
			center_y  += delta;
      break;
    case 'e':
			eye_y -= delta;
			center_y  -= delta;
      break;
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
			directionalLight_yTrans = -0.25f;
			break;
		case 'z':
			enableDirectionalLight();
			directionalLight_yTrans = 0.0f;
			break;
		case 'j':
			disablePointLight();
			pointLightSwitch_yTrans = -0.25f;
			break;
		case 'u':
			enablePointLight();
			pointLightSwitch_yTrans = 0.0f;
			break;
		case 'k':
			disableSpotLight();
			spotLightSwitch_yTrans = -0.25f;
			break;
		case 'i':
			enableSpotLight();
			spotLightSwitch_yTrans = 0.0f;
			break;
		case 'f':
		if(fogEnabled) {
			disableFog();
			fogEnabled = false;
			fog_switch_xTranslate = 0.0f;
		}
		else {
			enableFog();
			fogEnabled = true;
			fog_switch_xTranslate = 0.3f;
		}
  }

  glutPostRedisplay();
}


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
	glutTimerFunc(10, animateFigures, 0);

  glutMainLoop();
  return 0;
}