#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;


//make sure to make them readonly
double SCREEN_X = 4.6; //Width = 2 * SCREEN_X
double SCREEN_Y = 3.0; //height = 2 * SCREEN_Y

void MyKeyboardFunc(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27: ///ESC key.
            exit(0);
        break;
        case 13:  ///Enter key.
            //startGame = 1;
        break;

        case 'P':
        case 'p':
//            pause = (pause)?false:true;
  //          cout<<pause<<" ";
        break;
        default:
        break;
    }
}
