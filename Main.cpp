#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <MMSystem.h>
#include <vector>
#include <cstdlib>

#include "kitcatEngine.hpp"
#include "cat.hpp"

using namespace std;

int SCORE = 0;
float _angle = 0.0f;
float _cameraAngle = 0.0f;
vector<Food> foodList;

Cat kitty, catrina;

void initRendering();
void handleResize(int w, int h);
void MainMenu();
void GameMenu();
void GameOverMenu();
void drawScene();
void BackGround();
void update(int value);
void reset();
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
	PlaySound("countrysong.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
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
        case 'R':
        case 'r':
            reset();
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
            else if(STATE == GAME_FINISHED)
            {
                reset();
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
            break;
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
    glTranslatef(-SCREEN_X, -SCREEN_Y, 0);
    glScalef(7.6, 7.2, 1);

    BackGround();
    glPopMatrix();
    char buffer2 [50];
    sprintf (buffer2, "Score : %d", SCORE);
    glColor3ub(255,0,0);
    DrawBitmapString(-4, 2.6, (void *)FONT_TIMES_ROMAN_24, buffer2);
    glPushMatrix();
    glTranslatef(-2.9, -2, 0);
    kitty.drawBody();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.1, -2, 0);
    catrina.drawBody();
    glPopMatrix();

    for (int i = 0; i<foodList.size(); i++)
    {
        foodList[i].drawfood();
    }
}



void update(int value) {
    if(STATE == GAME_RUNNING)
    {
        int randFood = rand() % 100;
        if(randFood%14 == 0)  ///generate random food.
        {
            Food f;
            if(randFood%28==0 && randFood%8==0)
            {
                f.FOOD_CATEGORY = f.CATEGORY_BOMB;
                f.Food_Value = 0;
            }
            else if(randFood%10 == 0)
            {
                f.FOOD_CATEGORY = f.CATEGORY_SPECIAL;
                f.Food_Value = 3;
            }
            cout<<"CATEGORY : "<<f.FOOD_CATEGORY<<endl;
            foodList.push_back(f);
        }
        for (int i = 0; i<foodList.size(); i++)
        {
            if(foodList[i].t >= 0.96)
            {
                if(foodList[i].FOOD_CATEGORY == Food::CATEGORY_BOMB)
                {
                    if(catrina.MOUTH_STATUS == Cat::MOUTH_OPEN && foodList[i].ALIGN == Food::LEFT2RIGHT)
                    {
                        STATE = GAME_FINISHED;
                    }
                    else if(kitty.MOUTH_STATUS == Cat::MOUTH_OPEN && foodList[i].ALIGN == Food::RIGHT2LEFT)
                    {
                        STATE = GAME_FINISHED;
                    }
                    foodList.erase(foodList.begin()+i);
                }
                else
                {
                    if(catrina.MOUTH_STATUS == Cat::MOUTH_OPEN && foodList[i].ALIGN == Food::LEFT2RIGHT)
                    {
                        SCORE+=foodList[i].Food_Value;
                        foodList.erase(foodList.begin()+i);
                    }
                    else if(kitty.MOUTH_STATUS == Cat::MOUTH_OPEN && foodList[i].ALIGN == Food::RIGHT2LEFT)
                    {
                        SCORE+=foodList[i].Food_Value;
                        foodList.erase(foodList.begin()+i);
                    }
                    else
                    {
                        STATE = GAME_FINISHED;
                    }
                }
            }

        }
        for (int i = 0; i<foodList.size(); i++)
        {
            foodList[i].drawline();
        }
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
        DrawBitmapString(-2.0, 1.2, (void *)FONT_TIMES_ROMAN_24, "Press ESC to EXIT & 'R/r' to RESTART");
        DrawBitmapString(-2.0, 0.9, (void *)FONT_TIMES_ROMAN_24, " Group No. 11");

        glColor3f(1,1,1);
        DrawBitmapString(-2.0, 0.4, (void *)FONT_TIMES_ROMAN_24, "*****#  Instructions  #*****");
        DrawBitmapString(-2.0, 0.1, (void *)FONT_TIMES_ROMAN_24, "1. Use Arrow LEFT/RIGHT to Feed The Cats.");
        DrawBitmapString(-2.0, -0.2,(void *)FONT_TIMES_ROMAN_24, "2. Avoid Non-Edible Objects.");
        DrawBitmapString(-2.0, -0.5,(void *)FONT_TIMES_ROMAN_24, "3. They are innocent, Don't kill them.");

        glColor3f(0,1,1);
        DrawBitmapString(-2.0, -1.0, (void *)FONT_TIMES_ROMAN_24, "Submitted By:");
        DrawBitmapString(-2.0, -1.2, (void *)FONT_TIMES_ROMAN_24, "Islam, Rakibul (15-29594-2)");
        DrawBitmapString(-2.0, -1.4, (void *)FONT_TIMES_ROMAN_24, "Arafat, Rafiul (15-29654-2)");
        DrawBitmapString(-2.0, -1.6, (void *)FONT_TIMES_ROMAN_24, "Uddin, Borhan (15-29797-2)");
        DrawBitmapString(-2.0, -1.8, (void *)FONT_TIMES_ROMAN_24, "Hossain, Khalid (15-29666-2)");
}

void GameOverMenu()
{
    glColor3f(1,0,0);
    DrawBitmapString(-1.0, 1.0, (void *)FONT_TIMES_ROMAN_24, "GAME OVER !!!");
    glColor3f(1,1,0);
    char buffer3 [50];
    sprintf (buffer3, "Your Score is : %d", SCORE);
    DrawBitmapString(-1.0, 0.7, (void *)FONT_TIMES_ROMAN_24, buffer3);
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

void reset()
{
    SCORE = 0;
    STATE = GAME_NOT_STARTED;
    foodList.clear();
}
void BackGround()
{
    ///Floor Background
    glColor3f(0.53, 0.22, 0.22);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0, 0, -0.005);
    glVertex3f(0, 0.415, -0.005);
    glVertex3f(1.200, 0.415, -0.005);
    glVertex3f(1.200, 0, -0.005);

    ///Wall-e Background
    glColor3ub(212, 208, 239);
    glBegin(GL_QUADS);
    glVertex3f(0, 0.415, -0.005);
    glVertex3f(0, 0.800, -0.005);
    glVertex3f(1.200, 0.800, -0.005);
    glVertex3f(1.200, 0.415, -0.005);

    ///Floor Tiles
    ///===============================================
    glColor3f(0.95, 0.74, 0.55); ///
    glVertex3f(0, 0, -0.004);
    glVertex3f(0, 0.005, -0.004);
    glVertex3f(0.245, 0.005, -0.004);
    glVertex3f(0.245, 0, -0.004);

    glVertex3f(0.255, 0, -0.004);
    glVertex3f(0.255, 0.005, -0.004);
    glVertex3f(0.990, 0.005, -0.004);
    glVertex3f(0.990, 0, -0.004);

    glVertex3f(1.000, 0, -0.004);
    glVertex3f(1.000, 0.005, -0.004);
    glVertex3f(1.200, 0.005, -0.004);
    glVertex3f(1.200, 0, -0.004);

    glVertex3f(0, 0.010, -0.004);
    glVertex3f(0, 0.030, -0.004);
    glVertex3f(0.640, 0.030, -0.004);
    glVertex3f(0.640, 0.010, -0.004);

    glVertex3f(0.650, 0.010, -0.004);
    glVertex3f(0.650, 0.030, -0.004);
    glVertex3f(1.200, 0.030, -0.004);
    glVertex3f(1.200, 0.010, -0.004);

    glVertex3f(0, 0.035, -0.004);
    glVertex3f(0, 0.055, -0.004);
    glVertex3f(0.245, 0.055, -0.004);
    glVertex3f(0.245, 0.035, -0.004);

    glVertex3f(0.255, 0.035, -0.004);
    glVertex3f(0.255, 0.055, -0.004);
    glVertex3f(0.990, 0.055, -0.004);
    glVertex3f(0.990, 0.035, -0.004);

    glVertex3f(1.000, 0.035, -0.004);
    glVertex3f(1.000, 0.055, -0.004);
    glVertex3f(1.200, 0.055, -0.004);
    glVertex3f(1.200, 0.035, -0.004);

    glVertex3f(0, 0.060, -0.004);
    glVertex3f(0, 0.080, -0.004);
    glVertex3f(0.640, 0.080, -0.004);
    glVertex3f(0.640, 0.060, -0.004);

    glVertex3f(0.650, 0.060, -0.004);
    glVertex3f(0.650, 0.080, -0.004);
    glVertex3f(1.200, 0.080, -0.004);
    glVertex3f(1.200, 0.060, -0.004);

    glVertex3f(0, 0.085, -0.004);
    glVertex3f(0, 0.105, -0.004);
    glVertex3f(0.245, 0.105, -0.004);
    glVertex3f(0.245, 0.085, -0.004);

    glVertex3f(0.255, 0.085, -0.004);
    glVertex3f(0.255, 0.105, -0.004);
    glVertex3f(0.990, 0.105, -0.004);
    glVertex3f(0.990, 0.085, -0.004);

    glVertex3f(1.000, 0.085, -0.004);
    glVertex3f(1.000, 0.105, -0.004);
    glVertex3f(1.200, 0.105, -0.004);
    glVertex3f(1.200, 0.085, -0.004);

    glVertex3f(0, 0.110, -0.004);
    glVertex3f(0, 0.130, -0.004);
    glVertex3f(0.640, 0.130, -0.004);
    glVertex3f(0.640, 0.110, -0.004);

    glVertex3f(0.650, 0.110, -0.004);
    glVertex3f(0.650, 0.130, -0.004);
    glVertex3f(1.200, 0.130, -0.004);
    glVertex3f(1.200, 0.110, -0.004);

    glVertex3f(0, 0.135, -0.004);
    glVertex3f(0, 0.155, -0.004);
    glVertex3f(0.245, 0.155, -0.004);
    glVertex3f(0.245, 0.135, -0.004);

    glVertex3f(0.255, 0.135, -0.004);
    glVertex3f(0.255, 0.155, -0.004);
    glVertex3f(0.990, 0.155, -0.004);
    glVertex3f(0.990, 0.135, -0.004);

    glVertex3f(1.000, 0.135, -0.004);
    glVertex3f(1.000, 0.155, -0.004);
    glVertex3f(1.200, 0.155, -0.004);
    glVertex3f(1.200, 0.135, -0.004);
    //Floor tiles ends
    ///==============================
    glColor3f(0,0,1); ///blue
    glVertex3f(0, 0.170, -0.004);
    glVertex3f(0, 0.355, -0.004);
    glVertex3f(0.445, 0.355, -0.004);
    glVertex3f(0.445, 0.170, -0.004);

    glVertex3f(0.460, 0.170, -0.004);
    glVertex3f(0.460, 0.355, -0.004);
    glVertex3f(0.970, 0.355, -0.004);
    glVertex3f(0.970, 0.170, -0.004);

    glVertex3f(0.985, 0.170, -0.004);
    glVertex3f(0.985, 0.355, -0.004);
    glVertex3f(1.200, 0.355, -0.004);
    glVertex3f(1.200, 0.170, -0.004);

    ///===================================================
    glVertex3f(0, 0.550, -0.004);
    glVertex3f(0, 0.775, -0.004);
    glVertex3f(0.485, 0.775, -0.004);
    glVertex3f(0.485, 0.550, -0.004);

    //window border
    glColor3f(0,1,1);
    glVertex3f(1.200, 0.765, -0.004);
    glVertex3f(1.200, 0.540, -0.004);
    glVertex3f(0.715, 0.540, -0.004);
    glVertex3f(0.715, 0.765, -0.004);
    ///window
    glColor3f(.197, .206, .224);
    glVertex3f(0.750, 0.555, -0.0035);
    glVertex3f(0.750, 0.625, -0.0035);
    glVertex3f(1.200, 0.625, -0.0035);
    glVertex3f(1.200, 0.555, -0.0035);

    glVertex3f(0.750, 0.650, -0.0035);
    glVertex3f(0.750, 0.755, -0.0035);
    glVertex3f(1.200, 0.755, -0.0035);
    glVertex3f(1.200, 0.650, -0.0035);
    ///window ends
    glEnd();
    ///sink start
    ///1
    glColor3ub(100, 104, 114);//(R,G,B)
    glBegin(GL_POLYGON);
    glVertex3f(0.179, 0.463, -0.004);//c
    glVertex3f(0.179, 0.474, -0.004);//b
    glVertex3f(0.399, 0.474, -0.004);//a
    glVertex3f(0.399, 0.468, -0.004);//f
    glVertex3f(0.409, 0.468, -0.004);//e
    glVertex3f(0.409, 0.463, -0.004);//d
    glEnd();
    ///2
    glColor3ub(65, 68, 76);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.169, 0.463, -0.004);//a
    glVertex3f(0.169, 0.415, -0.004);//b
    glVertex3f(0.420, 0.415, -0.004);//c
    glVertex3f(0.420, 0.463, -0.004);//d
    glEnd();
    ///3
    glColor3ub(127, 132, 145);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.193, 0.451, -0.004);//a
    glVertex3f(0.226, 0.451, -0.004);//b
    glVertex3f(0.226, 0.457, -0.004);//c
    glVertex3f(0.193, 0.457, -0.004);//d
    glEnd();

    //glColor3f(0.9, 0.22, 0.92);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.207, 0.451, -0.004);//a
    glVertex3f(0.207, 0.435, -0.004);//b
    glVertex3f(0.214, 0.435, -0.004);//c
    glVertex3f(0.214, 0.451, -0.004);//d
    glEnd();
    ///4
    glColor3ub(127, 132, 145);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.373, 0.454, -0.004);//a
    glVertex3f(0.382, 0.454, -0.004);//b
    glVertex3f(0.382, 0.457, -0.004);//c
    glVertex3f(0.373, 0.457, -0.004);//d
    glEnd();
    ///5
    glColor3ub(127, 132, 145);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.386, 0.435, -0.004);//a
    glVertex3f(0.402, 0.435, -0.004);//b
    glVertex3f(0.402, 0.444, -0.004);//c
    glVertex3f(0.386, 0.444, -0.004);//d
    glEnd();
    ///6
    glColor3ub(167, 188, 177);//(R,G,B)
    glBegin(GL_POLYGON);
    glVertex3f(0.165, 0.415, -0.004);//a
    glVertex3f(0.420, 0.415, -0.004);//b
    glVertex3f(0.420, 0.410, -0.004);//c
    glVertex3f(0.410, 0.410, -0.004);//d
    glVertex3f(0.410, 0.405, -0.004);
    glVertex3f(0.165, 0.405, -0.004);
    glEnd();

    ///7
    //glColor3f(0.9, 0.22, 0.92);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.160, 0.405, -0.004);//a
    glVertex3f(0.160, 0.410, -0.004);//b
    glVertex3f(0.165, 0.410, -0.004);//c
    glVertex3f(0.165, 0.405, -0.004);//d
    glEnd();

    ///Water
    ///1
    glColor3ub(106, 109, 107);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.747, 0.415, -0.004);//a
    glVertex3f(1.067, 0.415, -0.004);//b
    glVertex3f(1.067, 0.422, -0.004);//c
    glVertex3f(0.747, 0.422, -0.004);//d
    glEnd();
    ///2
    //glColor3f(0.9, 0.22, 0.32);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.752, 0.422, -0.004);//a
    glVertex3f(1.062, 0.422, -0.004);//b
    glVertex3f(1.062, 0.427, -0.004);//c
    glVertex3f(0.752, 0.427, -0.004);//d
    glEnd();
    ///3
    glColor3ub(75, 79, 76);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.860, 0.425, -0.004);//a
    glVertex3f(0.930, 0.425, -0.004);//b
    glVertex3f(0.935, 0.430, -0.004);//c
    glVertex3f(0.855, 0.430, -0.004);//d
    glEnd();
    ///4
    //glColor3f(0.9, 0.72, 0.32);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.855, 0.430, -0.004);//a
    glVertex3f(0.862, 0.430, -0.004);//b
    glVertex3f(0.862, 0.435, -0.004);//c
    glVertex3f(0.855, 0.435, -0.004);//d
    glEnd();
    ///5
    //glColor3f(0.9, 0.72, 0.32);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.935, 0.430, -0.004);//a
    glVertex3f(0.935, 0.435, -0.004);//b
    glVertex3f(0.928, 0.435, -0.004);//c
    glVertex3f(0.928, 0.430, -0.004);//d
    glEnd();
    ///6
    glColor3ub(73, 76, 74);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.887, 0.430, -0.004);//a
    glVertex3f(0.906, 0.430, -0.004);//b
    glVertex3f(0.906, 0.469, -0.004);//c
    glVertex3f(0.887, 0.469, -0.004);//d
    glEnd();
    ///7
    //glColor3f(0.9, 0.52, 0.12);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.887, 0.469, -0.004);//a
    glVertex3f(0.887, 0.460, -0.004);//b
    glVertex3f(0.870, 0.460, -0.004);//c
    glVertex3f(0.870, 0.469, -0.004);//d
    glEnd();
    ///water end
    ///window-inside
    ///down

    glColor3ub(109, 156, 232);//(R,G,B)
    glBegin(GL_QUADS);
    glVertex3f(0.750, 0.570, -0.003);//a
    glVertex3f(1.045, 0.624, -0.003);//b
    glVertex3f(0.806, 0.624, -0.003);//c
    glVertex3f(0.750, 0.614, -0.003);//d
    glEnd();

    //glColor3f(0.4, 0.42, 0.82);//(R,G,B)
    glBegin(GL_TRIANGLES);
    glVertex3f(1.200, 0.609, -0.003);//a
    glVertex3f(1.200, 0.555, -0.003);//b
    glVertex3f(0.926, 0.555, -0.003);//c
    glEnd();

    ///up
    //glColor3f(0.4, 0.42, 0.82);//(R,G,B)
    glBegin(GL_TRIANGLES);
    glVertex3f(0.952, 0.650, -0.003);//a
    glVertex3f(1.200, 0.700, -0.003);//b
    glVertex3f(1.200, 0.650, -0.003);//c
    glEnd();

    //glColor3f(0.48, 0.42, 0.82);//(R,G,B)
    glBegin(GL_TRIANGLES);
    glVertex3f(0.750, 0.654, -0.003);//a
    glVertex3f(0.750, 0.755, -0.003);//b
    glVertex3f(1.200, 0.755, -0.003);//c
    glEnd();
    ///cloud-1
    glColor3f(1, 1, .9);//(R,G,B)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.755, 0.729, -0.0025);//a
    glVertex3f(0.766, 0.729, -0.0025);//b
    glVertex3f(0.772, 0.723, -0.0025);//c
    glVertex3f(0.783, 0.723, -0.0025);
    glVertex3f(0.789, 0.732, -0.0025);
    glVertex3f(0.799, 0.732, -0.0025);
    glVertex3f(0.808, 0.727, -0.0025);
    glVertex3f(0.816, 0.727, -0.0025);
    glVertex3f(0.820, 0.735, -0.0025);
    glVertex3f(0.830, 0.735, -0.0025);
    glVertex3f(0.830, 0.738, -0.0025);
    glVertex3f(0.816, 0.738, -0.0025);
    glVertex3f(0.800, 0.745, -0.0025);
    glVertex3f(0.780, 0.735, -0.0025);
    glVertex3f(0.765, 0.735, -0.0025);
    glVertex3f(0.755, 0.729, -0.0025);
    glEnd();

    ///cloud-2
    glColor3f(1, 1, .9);//(R,G,B)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.833, 0.723, -0.0025);
    glVertex3f(0.859, 0.732, -0.0025);
    glVertex3f(0.849, 0.732, -0.0025);
    glVertex3f(0.858, 0.727, -0.0025);
    glVertex3f(0.866, 0.727, -0.0025);
    glVertex3f(0.870, 0.735, -0.0025);
    glVertex3f(0.880, 0.735, -0.0025);
    glVertex3f(0.880, 0.738, -0.0025);
    glVertex3f(0.866, 0.738, -0.0025);
    glVertex3f(0.850, 0.745, -0.0025);
    glVertex3f(0.833, 0.723, -0.0025);
    glEnd();
}
