#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;


float R2LX[3]={SCREEN_X, -2.6, -2.0}, R2LY[3]={SCREEN_Y-0.5, 2.5, -1};
float L2RX[3]={-SCREEN_X, 2.6, 2.0 }, L2RY[3]={SCREEN_Y-0.5, 2.5, -1};

class Food
{
    float ctrlPointsCount = 3;
    float foodSpeed = 0.01f;
    float ctrlPointsX[3], ctrlPointsY[3];
    double t = 0.0;
    float xval = 0.0f;
    float yval = 0.0f;



    float getNextBezierPointX(float t)
    {
        float x=0.0;
        for(int i=0; i<ctrlPointsCount; i++)
        {
            int c;
            if(i==0 || i==ctrlPointsCount-1) {c = 1;}
            else {c = ctrlPointsCount-1;}
            x +=  c * pow(t, i) * pow(1-t, ctrlPointsCount-1-i) * ctrlPointsX[i];
        }
        return x;
    }
    float getNextBezierPointY(float t)
    {
        float y=0.0;
        for(int i=0; i<ctrlPointsCount; i++)
        {
            int c;
            if(i==0 || i==ctrlPointsCount-1){ c = 1; }
            else{ c = ctrlPointsCount-1; }
            y +=  c * pow(t, i) * pow(1-t, ctrlPointsCount-1-i) * ctrlPointsY[i];
        }
        return y;
    }
public:
    Food()
    {
        std::cout<<"Food Created\n";

        for(int i=0;i<3;i++)
        {
            ctrlPointsX[i] = R2LX[i];
            ctrlPointsY[i] = R2LY[i];
        }
    }
    ~Food()
    {
        std::cout<<"Food Dest\n";
    }
    void drawline()
    {
        /*float oldX=ctrlPointsX[0], oldY=ctrlPointsY[0];
        for(double t = 0.0;t <= 1.0; t += 0.01) {
		float x = getNextBezierPointX(t);
		float y = getNextBezierPointY(t);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(oldX, oldY, 0.001);
		glVertex3f(x, y, 0.001);
		glEnd();

		oldX = x;
		oldY = y;
    }*/
        float oldX=ctrlPointsX[0], oldY=ctrlPointsY[0];
        if(t <= 1.0) {
            xval = getNextBezierPointX(t);
            yval = getNextBezierPointY(t);

            oldX = xval;
            oldY = yval;
        }
        t += foodSpeed;
    }
    void drawfood()
    {
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        glVertex3f(xval, yval, 0.001);
        glVertex3f(xval, yval+0.5, 0.001);
        glVertex3f(xval+0.5, yval+0.5, 0.001);
        glVertex3f(xval+0.5, yval, 0.001);
        glEnd();
    }
};

///Cat Object
class Cat
{
public:
    const static int ALIVE = 0;
    const static int DEAD = 1;
    const static int MOUTH_CLOSE = 10;
    const static int MOUTH_OPEN = 11;

    int STATUS;
    int MOUTH_STATUS;

    Cat()
    {
        std::cout<<"Cat Created\n";
        STATUS = ALIVE; ///life status
        MOUTH_STATUS = MOUTH_CLOSE; ///mouth status
    }
    ~Cat()
    {
        std::cout<<"Dest\n";
    }

    void drawBody()
    {
        if(STATUS == ALIVE)
        {
            glColor3ub(200,255,255);
            ///back leg left
            glBegin(GL_POLYGON);
            glVertex3f(0.544, 0.368, 0);
            glVertex3f(0.6, 0.192, 0);
            glVertex3f(0.6, 0.08, 0);
            glVertex3f(0.54, 0.04, 0);
            glVertex3f(0.36, 0.04, 0);
            glVertex3f(0.286, 0.18, 0);
            glVertex3f(0.296, 0.448, 0);
            glVertex3f(0.448, 0.744, 0);
            glVertex3f(0.46, 0.828, 0);
            glVertex3f(0.704, 0.828, 0);
            glEnd();
            ///back leg right
            glBegin(GL_POLYGON);
            glVertex3f(1.264, 0.368, 0);
            glVertex3f(1.108, 0.828, 0);
            glVertex3f(1.348, 0.828, 0);
            glVertex3f(1.4, 0.744, 0);
            glVertex3f(1.52, 0.444, 0);
            glVertex3f(1.544, 0.18, 0);
            glVertex3f(1.452, 0.04, 0);
            glVertex3f(1.272, 0.04, 0);
            glVertex3f(1.224, 0.08, 0);
            glVertex3f(1.224, 0.192, 0);
            glEnd();
            ///front leg left
            glBegin(GL_POLYGON);
            glVertex3f(0.544, 0.368, 0);
            glVertex3f(0.708, 0.04, 0);
            glVertex3f(0.836, 0.04, 0);
            glVertex3f(0.836, 0.072, 0);
            glVertex3f(0.808, 0.096, 0);
            glVertex3f(0.836, 0.16, 0);
            glVertex3f(0.836, 0.284, 0);
            glVertex3f(0.836, 0.828, 0);
            glVertex3f(0.704, 0.828, 0);
            glEnd();
            ///front leg right
            glBegin(GL_POLYGON);
            glVertex3f(1.264, 0.368, 0);
            glVertex3f(1.132, 0.04, 0);
            glVertex3f(0.972, 0.04, 0);
            glVertex3f(0.972, 0.072, 0);
            glVertex3f(1.008, 0.096, 0);
            glVertex3f(0.976, 0.16, 0);
            glVertex3f(0.976, 0.284, 0);
            glVertex3f(0.976, 0.828, 0);
            glVertex3f(1.108, 0.828, 0);
            glEnd();
            ///body
            glColor3ub(255,255,255);
            glBegin(GL_QUADS);
            glVertex3f(0.836, 0.828, 0);
            glVertex3f(0.976, 0.828, 0);
            glVertex3f(0.976, 0.2, 0);
            glVertex3f(0.836, 0.2, 0);
            glEnd();
            ///head
            glColor3ub(255, 255, 0);
            glBegin(GL_POLYGON);
            glVertex3f(0.46, 0.828, 0);
            glVertex3f(0.3, 1.02, 0);
            glVertex3f(0.3, 1.26, 0);
            glVertex3f(0.328, 1.36, 0);
            glVertex3f(0.6, 1.8, 0);
            glVertex3f(0.7, 1.8, 0);
            glVertex3f(0.784, 1.696, 0);
            glVertex3f(0.84, 1.668, 0);
            glVertex3f(0.9, 1.668, 0);
            glVertex3f(0.9, 0.828, 0);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(1.352, 0.828, 0);
            glVertex3f(1.512, 1.02, 0);
            glVertex3f(1.512, 1.26, 0);
            glVertex3f(1.484, 1.36, 0);
            glVertex3f(1.216, 1.8, 0);
            glVertex3f(1.108, 1.8, 0);
            glVertex3f(1.024, 1.696, 0);
            glVertex3f(0.972, 1.668, 0);
            glVertex3f(0.9, 1.668, 0);
            glVertex3f(0.9, 0.828, 0);
            glEnd();
            ///ear
            glColor3ub(100,100,100);
            glBegin(GL_TRIANGLES);
            glVertex3f(0.564, 1.664, 0.001);
            glVertex3f(0.648, 1.76, 0.001);
            glVertex3f(0.736, 1.664, 0.001);

            glVertex3f(1.08, 1.664, 0.001);
            glVertex3f(1.164, 1.76, 0.001);
            glVertex3f(1.252, 1.664, 0.001);
            glEnd();
            if(MOUTH_STATUS == MOUTH_OPEN)
            {
                ///mouth
                glColor3ub(255, 0, 0);
                glBegin(GL_POLYGON);
                glVertex3f(0.76, 0.92, 0.001);
                glVertex3f(0.68, 1.08, 0.001);
                glVertex3f(0.8, 1.12, 0.001);
                glVertex3f(0.96, 1.12, 0.001);
                glVertex3f(1.08, 1.08, 0.001);
                glVertex3f(1, 0.92, 0.001);
                glEnd();
                ///left eye
                glColor3ub(0,0,0);
                glBegin(GL_QUADS);
                glVertex3f(0.440, 1.160, 0.001);
                glVertex3f(0.400, 1.240, 0.001);
                glVertex3f(0.644, 1.364, 0.001);
                glVertex3f(0.684, 1.280, 0.001);
                ///right eye
                glBegin(GL_QUADS);
                glVertex3f(1.04, 1.28, 0.001);
                glVertex3f(1.08, 1.36, 0.001);
                glVertex3f(1.32, 1.24, 0.001);
                glVertex3f(1.28, 1.16, 0.001);
                glEnd();
            }
            else
            {
                ///mouth
                glColor3ub(100,100,255);
                glBegin(GL_QUADS);
                glVertex3f(0.836, 0.988, 0.001);
                glVertex3f(0.864, 0.988, 0.001);
                glVertex3f(0.904, 1.048, 0.001);
                glVertex3f(0.892, 1.072, 0.001);

                glVertex3f(0.952, 0.988, 0.001);
                glVertex3f(0.972, 0.988, 0.001);
                glVertex3f(0.92, 1.072, 0.001);
                glVertex3f(0.892, 1.072, 0.001);

                glVertex3f(0.892, 1.1, 0.001);
                glVertex3f(0.92, 1.1, 0.001);
                glVertex3f(0.92, 1.128, 0.001);
                glVertex3f(0.892, 1.128, 0.001);
                glEnd();
                glColor3ub(0,0,0.001);
                ///left eye
                glBegin(GL_QUADS);
                glVertex3f(0.46, 1.42, 0.001);
                glVertex3f(0.84, 1.42, 0.001);
                glVertex3f(0.84, 1.32, 0.001);
                glVertex3f(0.46, 1.32, 0.001);

                glVertex3f(0.84, 1.232, 0.001);
                glVertex3f(0.92, 1.232, 0.001);
                glVertex3f(0.92, 1.32, 0.001);
                glVertex3f(0.84, 1.32, 0.001);

                glVertex3f(0.46, 1.232, 0.001);
                glVertex3f(0.488, 1.232, 0.001);
                glVertex3f(0.488, 1.32, 0.001);
                glVertex3f(0.46, 1.32, 0.001);

                glVertex3f(0.46, 1.232, 0.001);
                glVertex3f(0.56, 1.152, 0.001);
                glVertex3f(0.56, 1.18, 0.001);
                glVertex3f(0.488, 1.232, 0.001);

                glVertex3f(0.92, 1.232, 0.001);
                glVertex3f(0.84, 1.232, 0.001);
                glVertex3f(0.76, 1.152, 0.001);
                glVertex3f(0.76, 1.18, 0.001);

                glVertex3f(0.76, 1.152, 0.001);
                glVertex3f(0.56, 1.152, 0.001);
                glVertex3f(0.56, 1.18, 0.001);
                glVertex3f(0.76, 1.18, 0.001);

                glVertex3f(0.6, 1.176, 0.001);
                glVertex3f(0.6, 1.32, 0.001);
                glVertex3f(0.724, 1.32, 0.001);
                glVertex3f(0.724, 1.176, 0.001);

                ///right eye
                glBegin(GL_QUADS);
                glVertex3f(0.972, 1.42, 0.001);
                glVertex3f(1.352, 1.42, 0.001);
                glVertex3f(1.352, 1.32, 0.001);
                glVertex3f(0.972, 1.32, 0.001);

                glVertex3f(1.352, 1.232, 0.001);
                glVertex3f(1.324, 1.232, 0.001);
                glVertex3f(1.324, 1.32, 0.001);
                glVertex3f(1.352, 1.32, 0.001);

                glVertex3f(0.972, 1.232, 0.001);
                glVertex3f(1, 1.232, 0.001);
                glVertex3f(1, 1.32, 0.001);
                glVertex3f(0.972, 1.32, 0.001);

                glVertex3f(0.972, 1.232, 0.001);
                glVertex3f(1.072, 1.152, 0.001);
                glVertex3f(1.072, 1.18, 0.001);
                glVertex3f(1.000, 1.232, 0.001);

                glVertex3f(1.324, 1.232, 0.001);
                glVertex3f(1.352, 1.232, 0.001);
                glVertex3f(1.272, 1.152, 0.001);
                glVertex3f(1.272, 1.18, 0.001);

                glVertex3f(1.272, 1.152, 0.001);
                glVertex3f(1.072, 1.152, 0.001);
                glVertex3f(1.072, 1.18, 0.001);
                glVertex3f(1.272, 1.18, 0.001);

                glVertex3f(1.112, 1.176, 0.001);
                glVertex3f(1.112, 1.32, 0.001);
                glVertex3f(1.236, 1.32, 0.001);
                glVertex3f(1.236, 1.176, 0.001);
                glEnd();
            }

        }
    }
};
