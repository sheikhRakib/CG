#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

///Screen size
const double SCREEN_X = 4.60; //Width = 2 * SCREEN_X
const double SCREEN_Y = 2.89; //height = 2 * SCREEN_Y

///Game States
const int GAME_NOT_STARTED = 0;
const int GAME_RUNNING = 1;
const int GAME_PAUSED = 2;
const int GAME_FINISHED = 3;

int STATE = GAME_NOT_STARTED; /// initial game state

///Fonts
const int FONT_TIMES_ROMAN_24 = (int)GLUT_BITMAP_TIMES_ROMAN_24;

///to draw strings
void DrawBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
