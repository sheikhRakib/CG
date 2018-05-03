#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <MMSystem.h>
#include "kitcatEngine.hpp"
#include "cat.hpp"

using namespace std;

float _angle = 0.0f;
float _cameraAngle = 0.0f;

Cat kitty, catrina;
Food f,d;


void initRendering();
void handleResize(int w, int h);
void MainMenu();
void GameMenu();
void GameOverMenu();
void drawScene();
void update(int value);

void KeyboardListener(unsigned char Key, int x, int y);
void specialKeyboardListener(int key, int x, int y);
void keyBoardUp( int key, int x, int y );




int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(200,100);
	glutCreateWindow("KitCat");
	initRendering();

	glutDisplayFunc(drawScene);
    glutKeyboardFunc(KeyboardListener);
    glutSpecialFunc(specialKeyboardListener);
    glutSpecialUpFunc(keyBoardUp);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0); //Add a timer
    glutFullScreen();
	//PlaySound("countrysong.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	glutMainLoop();
	return 0;
}



void KeyboardListener(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27: ///ESC key.
            exit(0);
            break;
        case 13: ///Enter Key
            if(STATE == GAME_NOT_STARTED || STATE == GAME_PAUSED)
            {
                STATE = GAME_RUNNING;
            }
            else if(STATE == GAME_RUNNING)
            {
                STATE = GAME_PAUSED;
            }
            break;
        default:
            break;
    }
}
void specialKeyboardListener(int key, int x, int y) {
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            catrina.MOUTH_STATUS = catrina.MOUTH_OPEN;
            break;
        case GLUT_KEY_LEFT:
            kitty.MOUTH_STATUS = kitty.MOUTH_OPEN;
            break;
        default:
            break;
   }

}


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///camera setup
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -7.0);
    ///end camera setup

    switch(STATE)
    {
        case GAME_NOT_STARTED : ///game not started yet
        case GAME_PAUSED : ///game paused
            MainMenu();
            //break;
        case GAME_RUNNING :  ///game running
            GameMenu();
            break;
        case GAME_FINISHED : ///game finished
            GameOverMenu();
            break;
    }
    glutSwapBuffers();
}

void GameMenu()
{
    glPushMatrix();
    glTranslatef(-2.9, -2, 0);
    kitty.drawBody();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.1, -2, 0);
    catrina.drawBody();
    glPopMatrix();

    f.drawfood();
    }






void update(int value) {
    if(STATE == GAME_RUNNING)
    {
        f.drawline();


        _angle += 2.0f;
        if (_angle > 360) {
            _angle -= 360;
        }

    }
    glutPostRedisplay(); //Tell GLUT that the display has changed
	glutTimerFunc(25, update, 0);
}
void keyBoardUp( int key, int x, int y )
{
    switch(key) {
        case GLUT_KEY_RIGHT:
            catrina.MOUTH_STATUS = catrina.MOUTH_CLOSE;
            break;
        case GLUT_KEY_LEFT:
            kitty.MOUTH_STATUS = kitty.MOUTH_CLOSE;
            break;
    }
}





















///MENU
void MainMenu()
{
    glColor3f(1,1,0);
        DrawBitmapString(-1.0,2.0,(void *)FONT_TIMES_ROMAN_24,"_____| KitCat |_____");

        glColor3f(0,1,0);
        DrawBitmapString(-2.0, 1.5, (void *)FONT_TIMES_ROMAN_24, "Press ENTER to START/PAUSE");
        DrawBitmapString(-2.0, 1.2, (void *)FONT_TIMES_ROMAN_24, "Press ESC to EXIT");
        DrawBitmapString(-2.0, 0.9, (void *)FONT_TIMES_ROMAN_24, " Group No. 11");

        glColor3f(1,1,1);
        DrawBitmapString(-2.0, 0.4, (void *)FONT_TIMES_ROMAN_24, "*****#  Instructions  #*****");
        DrawBitmapString(-2.0, 0.1, (void *)FONT_TIMES_ROMAN_24, "1. Use Arrow LEFT/RIGHT to Feed The Cats.");
        DrawBitmapString(-2.0, -0.2,(void *)FONT_TIMES_ROMAN_24, "2. Avoid Non-Edible Objects.");
        DrawBitmapString(-2.0, -0.5,(void *)FONT_TIMES_ROMAN_24, "3. They are innocent, Don't kill them.");

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
