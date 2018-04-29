#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "kitcatEngine.hpp"
#include "cat.hpp"
#include <windows.h>
#include <MMSystem.h>

using namespace std;

float _angle = 0.0;
float _cameraAngle = 0.0;
Cat c;

void initRendering();
void handleResize(int w, int h);
void MainMenu();
void GameOverMenu();

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///camera setup
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units
    ///end camera setup

    switch(STATE)
    {
    case GAME_NOT_STARTED :
    case GAME_PAUSED :
        GameOverMenu();
        //MainMenu(); ///display the main menu
        break;
    case GAME_RUNNING :
        glPushMatrix();
        //glTranslatef(-SCREEN_X, -SCREEN_Y, 0);
        glScalef(2,2,1);
        glRotatef(_angle,1,1,1);
        //glScalef(_angle/2,_angle/2,_angle/2);

        c.drawBody();
        //DrawBackground();
        glPopMatrix();
        ///gamemenu
        break;
    case GAME_FINISHED :
        ///display score
        break;
    }
	glutSwapBuffers();
}

void update(int value) {
    if(STATE == GAME_RUNNING)
    {
        _angle += 2.0f;
        if (_angle > 360) {
            _angle -= 360;
        }
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	///Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(200,100);

	///Create the window
	glutCreateWindow("KitCat");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
    glutKeyboardFunc(KeyboardListener);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0); //Add a timer
    glutFullScreen();
	PlaySound("1.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	//sndPlaySound(TEXT("1.wav"), NULL, SND_SYNC);
	glutMainLoop();
	return 0;
}
























///init function
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}
///resize handler
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

///MENU
void MainMenu()
{
    glColor3f(1,1,0);
        DrawBitmapString(-1.0,2.0,(void *)FONT_TIMES_ROMAN_24,"----| KitCat |----");

        glColor3f(0,1,0);
        DrawBitmapString(-2.0, 1.5, (void *)FONT_TIMES_ROMAN_24, "Press ENTER to START/PAUSE");
        DrawBitmapString(-2.0, 1.2, (void *)FONT_TIMES_ROMAN_24, "Press ESC to EXIT");
        DrawBitmapString(-2.0, 0.9, (void *)FONT_TIMES_ROMAN_24, " Group No. 11");

        glColor3f(1,1,1);
        DrawBitmapString(-2.0, 0.4, (void *)FONT_TIMES_ROMAN_24, "*****#  Instructions  #*****");
        DrawBitmapString(-2.0, 0.1, (void *)FONT_TIMES_ROMAN_24, "1. Use Arrow LEFT/RIGHT to Feed The Cats.");
        DrawBitmapString(-2.0, -0.2,(void *)FONT_TIMES_ROMAN_24, "2. Avoid Non-Eatable Objects.");
        DrawBitmapString(-2.0, -0.5,(void *)FONT_TIMES_ROMAN_24, "3. They are innocent, Don't make them dead.");

        glColor3f(0,1,1);
        DrawBitmapString(-2.0, -1.0, (void *)FONT_TIMES_ROMAN_24, "Submitted By:");
        DrawBitmapString(-2.0, -1.2, (void *)FONT_TIMES_ROMAN_24, "Islam, Rakibul (15-29594-2)");
        DrawBitmapString(-2.0, -1.4, (void *)FONT_TIMES_ROMAN_24, "Arafat, Rafiul (15-xxxxx-2)");
        DrawBitmapString(-2.0, -1.6, (void *)FONT_TIMES_ROMAN_24, "Uddin, Borhan (15-xxxxx-2)");
        DrawBitmapString(-2.0, -1.8, (void *)FONT_TIMES_ROMAN_24, "Hossain, Khalid (15-xxxxx-2)");
}

void GameOverMenu()
{
    glColor3f(1,0,0);
    DrawBitmapString(-1.0, 1.0, (void *)FONT_TIMES_ROMAN_24, "GAME OVER !!!");
    glColor3f(1,1,0);
    DrawBitmapString(-1.0, 0.7, (void *)FONT_TIMES_ROMAN_24, "Your Score is : 500");
    glColor3f(0,1,0);
    DrawBitmapString(-1.0, 0.2, (void *)FONT_TIMES_ROMAN_24, "Press ENTER to START Again");
    DrawBitmapString(-1.0, 0.0, (void *)FONT_TIMES_ROMAN_24, "Press ESC to EXIT");
}
