#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

///Screen
const double SCREEN_X = 4.60; //Width = 2 * SCREEN_X
const double SCREEN_Y = 2.85; //height = 2 * SCREEN_Y

///Game States
const int GAME_NOT_STARTED = 0;
const int GAME_RUNNING = 1;
const int GAME_PAUSED = 2;
const int GAME_FINISHED = 3;

int STATE = GAME_NOT_STARTED; ///game state

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



void DrawBackground()
{
    glutWireCube(.5);
    glutWireCube(1);
    glutWireCube(1.5);
    glutWireCube(2);
    glutWireCube(2.5);
    glutWireCube(3);
}
