#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
///photo size 270 x 257
class Cat
{
public:
    const int ALIVE = 0;
    const int DEAD = 1;

    const int MOUTH_CLOSE = 10;
    const int MOUTH_OPEN = 11;

    int STATUS;
    int MOUTH_STATUS;

    Cat()
    {
        std::cout<<"Cat Created";
        STATUS = ALIVE; ///life status
        MOUTH_STATUS = MOUTH_CLOSE; ///mouth status
    }
    ~Cat()
    {
        cout<<"Dest\n";
    }
    void print()
    {
        cout<<"Lalala\n";
    }
    void drawBody()
    {
        glutWireCube(0.1);
        glutWireCube(0.2);
        glutWireCube(0.3);
        glutWireCube(0.4);
        glutWireCube(0.5);
        if(STATUS == ALIVE)
        {
            if(MOUTH_STATUS = MOUTH_OPEN)
            {
                ///TODO Draw Open Mouth
            }
            else
            {
                ///normal mouth
            }








        }
    }
};
