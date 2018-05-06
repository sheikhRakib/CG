#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
using namespace std;


float R2LX[3]={SCREEN_X, -2.6, -2.0}, R2LY[3]={SCREEN_Y-0.5, 2.5, -1};
float L2RX[3]={-SCREEN_X, 2.6, 2.0 }, L2RY[3]={SCREEN_Y-0.5, 2.5, -1};

class Food
{
    float ctrlPointsCount = 3;
    float foodSpeed = 0.005f;
    float ctrlPointsX[3], ctrlPointsY[3];
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
    void NormFoodL2R()
    {
        ///body
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.5,0.0);

        glVertex3f(0.420, -0.100, 0.002);
        glVertex3f(0.260, 0.060, 0.002);
        glVertex3f(-0.140, -0.100, 0.002);
        glVertex3f(0.300, -0.180, 0.002);
        glEnd();

        ///tail
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);

        glVertex3f(-0.140, -0.100, 0.002);
        glVertex3f(-0.220, -0.020, 0.002);
        glVertex3f(-0.180, -0.100, 0.002);
        glVertex3f(-0.220, -0.180, 0.002);
        glVertex3f(-0.140, -0.100, 0.002);
        glEnd();

        ///upper body
        glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);

        glVertex3f(0.260, 0.060, 0.002);
        glVertex3f(0.220, 0.100, 0.002);
        glVertex3f(-0.060, -0.064, 0.002);
        glVertex3f(0.260, 0.060, 0.002);
        glEnd();

        ///Mouth
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);

        glVertex3f(0.300, -0.180, 0.003);
        glVertex3f(0.220, -0.100, 0.003);
        glVertex3f(0.260, -0.172, 0.003);
        glVertex3f(0.300, -0.180, 0.003);
        glEnd();
    }

    void NormFoodR2L()
    {
        ///body
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.5,0.0);

        glVertex3f(-0.420, -0.100, 0.002);
        glVertex3f(-0.260, 0.060, 0.002);
        glVertex3f(0.140, -0.100, 0.002);
        glVertex3f(-0.300, -0.180, 0.002);
        glEnd();

        ///tail
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);

        glVertex3f(0.140, -0.100, 0.002);
        glVertex3f(0.220, -0.020, 0.002);
        glVertex3f(0.180, -0.100, 0.002);
        glVertex3f(0.220, -0.180, 0.002);
        glVertex3f(0.140, -0.100, 0.002);
        glEnd();

        ///upper body
        glBegin(GL_POLYGON);
        glColor3f(1.0,1.0,1.0);

        glVertex3f(-0.260, 0.060, 0.002);
        glVertex3f(-0.220, 0.100, 0.002);
        glVertex3f(0.060, -0.064, 0.002);
        glVertex3f(-0.260, 0.060, 0.002);
        glEnd();

        ///Mouth
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);

        glVertex3f(-0.300, -0.180, 0.003);
        glVertex3f(-0.220, -0.100, 0.003);
        glVertex3f(-0.260, -0.172, 0.003);
        glVertex3f(-0.300, -0.180, 0.003);
        glEnd();
    }
    void BombL2R()
    {
        glPushMatrix();
        glRotatef(180, 0.0, 0.0, 1.0);
        ///FishBomb
        ///Body
        glColor3ub(44, 45, 45);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.187, -0.211, 0.002);
        glVertex3f(-0.209, -0.210, 0.002);
        glVertex3f(-0.230, -0.207, 0.002);
        glVertex3f(-0.250, -0.203, 0.002);
        glVertex3f(-0.280, -0.197, 0.002);
        glVertex3f(-0.303, -0.193, 0.002);
        glVertex3f(-0.330, -0.185, 0.002);
        glVertex3f(-0.361, -0.173, 0.002);
        glVertex3f(-0.394, -0.159, 0.002);
        glVertex3f(-0.412, -0.144, 0.002);
        glVertex3f(-0.424, -0.136, 0.002);
        glVertex3f(-0.433, -0.126, 0.002);
        glVertex3f(-0.443, -0.115, 0.002);
        glVertex3f(-0.450, -0.100, 0.002);
        glVertex3f(-0.458, -0.088, 0.002);
        glVertex3f(-0.464, -0.072, 0.002);
        glVertex3f(-0.467, -0.056, 0.002);
        glVertex3f(-0.469, -0.044, 0.002);
        glVertex3f(-0.470, -0.029, 0.002);
        glVertex3f(-0.466, -0.009, 0.002);
        glVertex3f(-0.459, 0.008, 0.002);
        glVertex3f(-0.452, 0.026, 0.002);
        glVertex3f(-0.438, 0.044, 0.002);
        glVertex3f(-0.465, 0.060, 0.002);
        glVertex3f(-0.414, 0.064, 0.002);
        glVertex3f(-0.394, 0.080, 0.002);
        glVertex3f(-0.374, 0.088, 0.002);
        glVertex3f(-0.359, 0.095, 0.002);
        glVertex3f(-0.339, 0.104, 0.002);
        glVertex3f(-0.315, 0.114, 0.002);
        glVertex3f(-0.295, 0.119, 0.002);
        glVertex3f(-0.274, 0.126, 0.002);
        glVertex3f(-0.256, 0.129, 0.002);
        glVertex3f(-0.229, 0.135, 0.002);
        glVertex3f(-0.201, 0.137, 0.002);
        glVertex3f(-0.174, 0.141, 0.002);
        glVertex3f(-0.144, 0.140, 0.002);
        glVertex3f(-0.112, 0.136, 0.002);
        glVertex3f(-0.087, 0.134, 0.002);
        glVertex3f(-0.067, 0.132, 0.002);
        glVertex3f(-0.045, 0.127, 0.002);
        glVertex3f(-0.032, 0.124, 0.002);
        glVertex3f(-0.009, 0.115, 0.002);
        glVertex3f(0.010, 0.110, 0.002);
        glVertex3f(0.033, 0.097, 0.002);
        glVertex3f(0.054, 0.086, 0.002);
        glVertex3f(0.072, 0.073, 0.002);
        glVertex3f(0.089, 0.058, 0.002);
        glVertex3f(0.104, 0.056, 0.002);
        glVertex3f(0.116, 0.035, 0.002);
        glVertex3f(0.123, 0.021, 0.002);
        glVertex3f(0.132, 0.001, 0.002);
        glVertex3f(0.141, -0.023, 0.002);
        glVertex3f(0.144, -0.043, 0.002);
        glVertex3f(0.136, -0.063, 0.002);
        glVertex3f(0.128, -0.083, 0.002);
        glVertex3f(0.120, -0.097, 0.002);
        glVertex3f(0.107, -0.112, 0.002);
        glVertex3f(0.092, -0.127, 0.002);
        glVertex3f(0.078, -0.138, 0.002);
        glVertex3f(0.051, -0.155, 0.002);
        glVertex3f(0.035, -0.164, 0.002);
        glVertex3f(0.016, -0.174, 0.002);
        glVertex3f(-0.014, -0.188, 0.002);
        glVertex3f(-0.032, -0.196, 0.002);
        glVertex3f(-0.065, -0.205, 0.002);
        glVertex3f(-0.096, -0.209, 0.002);
        glVertex3f(-0.140, -0.214, 0.002);
        glVertex3f(-0.163, -0.213, 0.002);
        glEnd();
        ///UP
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(-0.187, -0.211, 0.002);
        glVertex3f(-0.183, -0.227, 0.002);
        glVertex3f(-0.178, -0.237, 0.002);
        glVertex3f(-0.167, -0.244, 0.002);
        glVertex3f(-0.147, -0.249, 0.002);
        glVertex3f(-0.137, -0.251, 0.002);
        glVertex3f(-0.119, -0.252, 0.002);
        glVertex3f(-0.090, -0.252, 0.002);
        glVertex3f(-0.070, -0.246, 0.002);
        glVertex3f(-0.050, -0.239, 0.002);
        glVertex3f(-0.039, -0.234, 0.002);
        glVertex3f(-0.033, -0.223, 0.002);
        glVertex3f(-0.030, -0.213, 0.002);
        glVertex3f(-0.032, -0.194, 0.002);
        glEnd();
        ///Tail
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(0.085, 0.060, 0.002);
        glVertex3f(0.089, 0.062, 0.002);
        glVertex3f(0.103, 0.047, 0.002);
        glVertex3f(0.109, 0.041, 0.002);
        glVertex3f(0.125, 0.039, 0.002);
        glVertex3f(0.134, 0.045, 0.002);
        glVertex3f(0.143, 0.050, 0.002);
        glVertex3f(0.153, 0.055, 0.002);
        glVertex3f(0.163, 0.059, 0.002);
        glVertex3f(0.177, 0.064, 0.002);
        glVertex3f(0.187, 0.067, 0.002);//
        glVertex3f(0.214, 0.074, 0.002);
        glVertex3f(0.138, 0.077, 0.002);
        glVertex3f(0.273, 0.081, 0.002);
        glVertex3f(0.297, 0.084, 0.002);
        glVertex3f(0.245, -0.004, 0.002);
        glVertex3f(0.342, -0.072, 0.002);
        glVertex3f(0.303, -0.081, 0.002);
        glVertex3f(0.263, -0.084, 0.002);
        glVertex3f(0.233, -0.082, 0.002);
        glVertex3f(0.205, -0.080, 0.002);
        glVertex3f(0.180, -0.077, 0.002);
        glVertex3f(0.160, -0.073, 0.002);
        glVertex3f(0.147, -0.069, 0.002);
        glVertex3f(0.136, -0.063, 0.002);
        glEnd();

        ///Upper Tail
        glColor3f(1, 1, 1);//(R,G,B)
        glBegin(GL_LINES);
        glVertex3f(-0.088, -0.249, 0.002);
        glVertex3f(-0.087, -0.257, 0.002);
        glVertex3f(-0.084, -0.267, 0.002);
        glVertex3f(-0.081, -0.276, 0.002);
        glVertex3f(-0.074, -0.280, 0.002);
        glVertex3f(-0.063, -0.287, 0.002);
        glVertex3f(-0.053, -0.290, 0.002);
        glVertex3f(-0.040, -0.293, 0.002);
        glVertex3f(-0.029, -0.292, 0.002);
        glVertex3f(-0.016, -0.292, 0.002);
        glVertex3f(-0.007, -0.289, 0.002);
        glVertex3f(0.003, -0.287, 0.002);
        glVertex3f(0.009, -0.286, 0.002);
        glVertex3f(0.019, -0.283, 0.002);
        glVertex3f(0.031, -0.280, 0.002);
        glVertex3f(0.041, -0.275, 0.002);
        glVertex3f(0.049, -0.276, 0.002);
        glVertex3f(0.052, -0.277, 0.002);
        glVertex3f(0.052, -0.281, 0.002);
        glVertex3f(0.051, -0.284, 0.002);
        glVertex3f(0.047, -0.285, 0.002);
        glVertex3f(0.041, -0.288, 0.002);
        glVertex3f(0.033, -0.292, 0.002);
        glVertex3f(0.027, -0.293, 0.002);
        glVertex3f(0.022, -0.296, 0.002);
        glVertex3f(0.014, -0.297, 0.002);
        glVertex3f(0.007, -0.300, 0.002);
        glVertex3f(0.00, -0.300, 0.002);
        glVertex3f(-0.015, -0.302, 0.002);
        glVertex3f(-0.023, -0.301, 0.002);
        glVertex3f(-0.034, -0.302, 0.002);
        glVertex3f(-0.051, -0.300, 0.002);
        glVertex3f(-0.059, -0.299, 0.002);
        glVertex3f(-0.068, -0.297, 0.002);
        glVertex3f(-0.075, -0.294, 0.002);
        glVertex3f(-0.085, -0.291, 0.002);
        glVertex3f(-0.091, -0.286, 0.002);
        glVertex3f(-0.097, -0.281, 0.002);
        glVertex3f(-0.099, -0.271, 0.002);
        glVertex3f(-0.101, -0.262, 0.002);
        glVertex3f(-0.102, -0.251, 0.002);
        glEnd();
        ///Eye
        //Outside
        glColor3f(1, 1, 1);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.325, -0.105, 0.0025);
        glVertex3f(-0.323, -0.097, 0.0025);
        glVertex3f(-0.317, -0.090, 0.0025);
        glVertex3f(-0.310, -0.085, 0.0025);
        glVertex3f(-0.304, -0.082, 0.0025);
        glVertex3f(-0.295, -0.080, 0.0025);
        glVertex3f(-0.287, -0.076, 0.0025);
        glVertex3f(-0.276, -0.077, 0.0025);
        glVertex3f(-0.266, -0.079, 0.0025);
        glVertex3f(-0.256, -0.084, 0.0025);
        glVertex3f(-0.248, -0.087, 0.0025);
        glVertex3f(-0.239, -0.094, 0.0025);
        glVertex3f(-0.236, -0.101, 0.0025);
        glVertex3f(-0.233, -0.110, 0.0025);
        glVertex3f(-0.234, -0.118, 0.0025);
        glVertex3f(-0.240, -0.124, 0.0025);
        glVertex3f(-0.245, -0.127, 0.0025);
        glVertex3f(-0.253, -0.129, 0.0025);
        glVertex3f(-0.260, -0.131, 0.0025);
        glVertex3f(-0.272, -0.133, 0.0025);
        glVertex3f(-0.279, -0.135, 0.0025);
        glVertex3f(-0.283, -0.134, 0.0025);
        glVertex3f(-0.293, -0.132, 0.0025);
        glVertex3f(-0.304, -0.131, 0.0025);
        glVertex3f(-0.313, -0.126, 0.0025);
        glVertex3f(-0.317, -0.123, 0.0025);
        glVertex3f(-0.321, -0.118, 0.0025);
        glVertex3f(-0.305, -0.114, 0.0025);
        glEnd();
        ///Inner
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(-0.305, -0.104, 0.003);
        glVertex3f(-0.303, -0.100, 0.003);
        glVertex3f(-0.298, -0.096, 0.003);
        glVertex3f(-0.292, -0.096, 0.003);
        glVertex3f(-0.283, -0.098, 0.003);
        glVertex3f(-0.279, -0.101, 0.003);
        glVertex3f(-0.276, -0.101, 0.003);
        glVertex3f(-0.279, -0.111, 0.003);
        glVertex3f(-0.286, -0.112, 0.003);
        glVertex3f(-0.293, -0.113, 0.003);
        glVertex3f(-0.299, -0.112, 0.003);
        glEnd();
        glPopMatrix();
    }

    void BombR2L()
    {
        glPushMatrix();
        glRotatef(180, 0.0, 0.0, 1.0);
        ///FishBomb
        ///Body
        glColor3ub(44, 45, 45);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.187, -0.211, 0.002);
        glVertex3f(0.209, -0.210, 0.002);
        glVertex3f(0.230, -0.207, 0.002);
        glVertex3f(0.250, -0.203, 0.002);
        glVertex3f(0.280, -0.197, 0.002);
        glVertex3f(0.303, -0.193, 0.002);
        glVertex3f(0.330, -0.185, 0.002);
        glVertex3f(0.361, -0.173, 0.002);
        glVertex3f(0.394, -0.159, 0.002);
        glVertex3f(0.412, -0.144, 0.002);
        glVertex3f(0.424, -0.136, 0.002);
        glVertex3f(0.433, -0.126, 0.002);
        glVertex3f(0.443, -0.115, 0.002);
        glVertex3f(0.450, -0.100, 0.002);
        glVertex3f(0.458, -0.088, 0.002);
        glVertex3f(0.464, -0.072, 0.002);
        glVertex3f(0.467, -0.056, 0.002);
        glVertex3f(0.469, -0.044, 0.002);
        glVertex3f(0.470, -0.029, 0.002);
        glVertex3f(0.466, -0.009, 0.002);
        glVertex3f(0.459, 0.008, 0.002);
        glVertex3f(0.452, 0.026, 0.002);
        glVertex3f(0.438, 0.044, 0.002);
        glVertex3f(0.465, 0.060, 0.002);
        glVertex3f(0.414, 0.064, 0.002);
        glVertex3f(0.394, 0.080, 0.002);
        glVertex3f(0.374, 0.088, 0.002);
        glVertex3f(0.359, 0.095, 0.002);
        glVertex3f(0.339, 0.104, 0.002);
        glVertex3f(0.315, 0.114, 0.002);
        glVertex3f(0.295, 0.119, 0.002);
        glVertex3f(0.274, 0.126, 0.002);
        glVertex3f(0.256, 0.129, 0.002);
        glVertex3f(0.229, 0.135, 0.002);
        glVertex3f(0.201, 0.137, 0.002);
        glVertex3f(0.174, 0.141, 0.002);
        glVertex3f(0.144, 0.140, 0.002);
        glVertex3f(0.112, 0.136, 0.002);
        glVertex3f(0.087, 0.134, 0.002);
        glVertex3f(0.067, 0.132, 0.002);
        glVertex3f(0.045, 0.127, 0.002);
        glVertex3f(0.032, 0.124, 0.002);
        glVertex3f(0.009, 0.115, 0.002);
        glVertex3f(-0.010, 0.110, 0.002);
        glVertex3f(-0.033, 0.097, 0.002);
        glVertex3f(-0.054, 0.086, 0.002);
        glVertex3f(-0.072, 0.073, 0.002);
        glVertex3f(-0.089, 0.058, 0.002);
        glVertex3f(-0.104, 0.056, 0.002);
        glVertex3f(-0.116, 0.035, 0.002);
        glVertex3f(-0.123, 0.021, 0.002);
        glVertex3f(-0.132, 0.001, 0.002);
        glVertex3f(-0.141, -0.023, 0.002);
        glVertex3f(-0.144, -0.043, 0.002);
        glVertex3f(-0.136, -0.063, 0.002);
        glVertex3f(-0.128, -0.083, 0.002);
        glVertex3f(-0.120, -0.097, 0.002);
        glVertex3f(-0.107, -0.112, 0.002);
        glVertex3f(-0.092, -0.127, 0.002);
        glVertex3f(-0.078, -0.138, 0.002);
        glVertex3f(-0.051, -0.155, 0.002);
        glVertex3f(-0.035, -0.164, 0.002);
        glVertex3f(-0.016, -0.174, 0.002);
        glVertex3f(0.014, -0.188, 0.002);
        glVertex3f(0.032, -0.196, 0.002);
        glVertex3f(0.065, -0.205, 0.002);
        glVertex3f(0.096, -0.209, 0.002);
        glVertex3f(0.140, -0.214, 0.002);
        glVertex3f(0.163, -0.213, 0.002);
        glEnd();
        ///UP
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(0.187, -0.211, 0.002);
        glVertex3f(0.183, -0.227, 0.002);
        glVertex3f(0.178, -0.237, 0.002);
        glVertex3f(0.167, -0.244, 0.002);
        glVertex3f(0.147, -0.249, 0.002);
        glVertex3f(0.137, -0.251, 0.002);
        glVertex3f(0.119, -0.252, 0.002);
        glVertex3f(0.090, -0.252, 0.002);
        glVertex3f(0.070, -0.246, 0.002);
        glVertex3f(0.050, -0.239, 0.002);
        glVertex3f(0.039, -0.234, 0.002);
        glVertex3f(0.033, -0.223, 0.002);
        glVertex3f(0.030, -0.213, 0.002);
        glVertex3f(0.032, -0.194, 0.002);
        glEnd();
        ///Tail
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(-0.085, 0.060, 0.002);
        glVertex3f(-0.089, 0.062, 0.002);
        glVertex3f(-0.103, 0.047, 0.002);
        glVertex3f(-0.109, 0.041, 0.002);
        glVertex3f(-0.125, 0.039, 0.002);
        glVertex3f(-0.134, 0.045, 0.002);
        glVertex3f(-0.143, 0.050, 0.002);
        glVertex3f(-0.153, 0.055, 0.002);
        glVertex3f(-0.163, 0.059, 0.002);
        glVertex3f(-0.177, 0.064, 0.002);
        glVertex3f(-0.187, 0.067, 0.002);//
        glVertex3f(-0.214, 0.074, 0.002);
        glVertex3f(-0.138, 0.077, 0.002);
        glVertex3f(-0.273, 0.081, 0.002);
        glVertex3f(-0.297, 0.084, 0.002);
        glVertex3f(-0.245, -0.004, 0.002);
        glVertex3f(-0.342, -0.072, 0.002);
        glVertex3f(-0.303, -0.081, 0.002);
        glVertex3f(-0.263, -0.084, 0.002);
        glVertex3f(-0.233, -0.082, 0.002);
        glVertex3f(-0.205, -0.080, 0.002);
        glVertex3f(-0.180, -0.077, 0.002);
        glVertex3f(-0.160, -0.073, 0.002);
        glVertex3f(-0.147, -0.069, 0.002);
        glVertex3f(-0.136, -0.063, 0.002);
        glEnd();

        ///Upper Tail
        glColor3f(1, 1, 1);//(R,G,B)
        glBegin(GL_LINES);
        glVertex3f(0.088, -0.249, 0.002);
        glVertex3f(0.087, -0.257, 0.002);
        glVertex3f(0.084, -0.267, 0.002);
        glVertex3f(0.081, -0.276, 0.002);
        glVertex3f(0.074, -0.280, 0.002);
        glVertex3f(0.063, -0.287, 0.002);
        glVertex3f(0.053, -0.290, 0.002);
        glVertex3f(0.040, -0.293, 0.002);
        glVertex3f(0.029, -0.292, 0.002);
        glVertex3f(0.016, -0.292, 0.002);
        glVertex3f(0.007, -0.289, 0.002);
        glVertex3f(-0.003, -0.287, 0.002);
        glVertex3f(-0.009, -0.286, 0.002);
        glVertex3f(-0.019, -0.283, 0.002);
        glVertex3f(-0.031, -0.280, 0.002);
        glVertex3f(-0.041, -0.275, 0.002);
        glVertex3f(-0.049, -0.276, 0.002);
        glVertex3f(-0.052, -0.277, 0.002);
        glVertex3f(-0.052, -0.281, 0.002);
        glVertex3f(-0.051, -0.284, 0.002);
        glVertex3f(-0.047, -0.285, 0.002);
        glVertex3f(-0.041, -0.288, 0.002);
        glVertex3f(-0.033, -0.292, 0.002);
        glVertex3f(-0.027, -0.293, 0.002);
        glVertex3f(-0.022, -0.296, 0.002);
        glVertex3f(-0.014, -0.297, 0.002);
        glVertex3f(-0.007, -0.300, 0.002);
        glVertex3f(-0.00, -0.300, 0.002);
        glVertex3f(0.015, -0.302, 0.002);
        glVertex3f(0.023, -0.301, 0.002);
        glVertex3f(0.034, -0.302, 0.002);
        glVertex3f(0.051, -0.300, 0.002);
        glVertex3f(0.059, -0.299, 0.002);
        glVertex3f(0.068, -0.297, 0.002);
        glVertex3f(0.075, -0.294, 0.002);
        glVertex3f(0.085, -0.291, 0.002);
        glVertex3f(0.091, -0.286, 0.002);
        glVertex3f(0.097, -0.281, 0.002);
        glVertex3f(0.099, -0.271, 0.002);
        glVertex3f(0.101, -0.262, 0.002);
        glVertex3f(0.102, -0.251, 0.002);
        glEnd();
        ///Eye
        //Outside
        glColor3f(1, 1, 1);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.325, -0.105, 0.0025);
        glVertex3f(0.323, -0.097, 0.0025);
        glVertex3f(0.317, -0.090, 0.0025);
        glVertex3f(0.310, -0.085, 0.0025);
        glVertex3f(0.304, -0.082, 0.0025);
        glVertex3f(0.295, -0.080, 0.0025);
        glVertex3f(0.287, -0.076, 0.0025);
        glVertex3f(0.276, -0.077, 0.0025);
        glVertex3f(0.266, -0.079, 0.0025);
        glVertex3f(0.256, -0.084, 0.0025);
        glVertex3f(0.248, -0.087, 0.0025);
        glVertex3f(0.239, -0.094, 0.0025);
        glVertex3f(0.236, -0.101, 0.0025);
        glVertex3f(0.233, -0.110, 0.0025);
        glVertex3f(0.234, -0.118, 0.0025);
        glVertex3f(0.240, -0.124, 0.0025);
        glVertex3f(0.245, -0.127, 0.0025);
        glVertex3f(0.253, -0.129, 0.0025);
        glVertex3f(0.260, -0.131, 0.0025);
        glVertex3f(0.272, -0.133, 0.0025);
        glVertex3f(0.279, -0.135, 0.0025);
        glVertex3f(0.283, -0.134, 0.0025);
        glVertex3f(0.293, -0.132, 0.0025);
        glVertex3f(0.304, -0.131, 0.0025);
        glVertex3f(0.313, -0.126, 0.0025);
        glVertex3f(0.317, -0.123, 0.0025);
        glVertex3f(0.321, -0.118, 0.0025);
        glVertex3f(0.305, -0.114, 0.0025);
        glEnd();
        ///Inner
        glColor3ub(44, 45, 45);
        glBegin(GL_POLYGON);
        glVertex3f(0.305, -0.104, 0.003);
        glVertex3f(0.303, -0.100, 0.003);
        glVertex3f(0.298, -0.096, 0.003);
        glVertex3f(0.292, -0.096, 0.003);
        glVertex3f(0.283, -0.098, 0.003);
        glVertex3f(0.279, -0.101, 0.003);
        glVertex3f(0.276, -0.101, 0.003);
        glVertex3f(0.279, -0.111, 0.003);
        glVertex3f(0.286, -0.112, 0.003);
        glVertex3f(0.293, -0.113, 0.003);
        glVertex3f(0.299, -0.112, 0.003);
        glEnd();
        glPopMatrix();
    }

    void Special_APP_L2R()
    {
        glPushMatrix();
        glTranslatef(-0.5,-0.5, 0.002);
        glScalef(.7,.7,1);
        ///SpecialFish_1
        ///Body
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.715, 0.106, 0.002);
        glVertex3f(0.773, 0.108, 0.002);
        glVertex3f(0.824, 0.114, 0.002);
        glVertex3f(0.868, 0.122, 0.002);
        glVertex3f(0.911, 0.132, 0.002);
        glVertex3f(0.951, 0.145, 0.002);
        glVertex3f(0.985, 0.159, 0.002);
        glVertex3f(1.023, 0.175, 0.002);
        glVertex3f(1.053, 0.194, 0.002);
        glVertex3f(1.081, 0.215, 0.002);
        glVertex3f(1.105, 0.237, 0.002);
        glVertex3f(1.132, 0.262, 0.002);
        glVertex3f(1.151, 0.296, 0.002);
        glVertex3f(1.170, 0.323, 0.002);
        glVertex3f(1.184, 0.363, 0.002);
        glVertex3f(1.189, 0.406, 0.002);
        glVertex3f(1.188, 0.447, 0.002);
        glVertex3f(1.173, 0.495, 0.002);
        glVertex3f(1.148, 0.540, 0.002);
        glVertex3f(1.117, 0.573, 0.002);
        glVertex3f(1.075, 0.606, 0.002);
        glVertex3f(1.027, 0.635, 0.002);
        glVertex3f(0.955, 0.664, 0.002);
        glVertex3f(0.899, 0.680, 0.002);
        glVertex3f(0.844, 0.691, 0.002);
        glVertex3f(0.783, 0.697, 0.002);
        glVertex3f(0.725, 0.701, 0.002);
        glVertex3f(0.655, 0.701, 0.002);
        glVertex3f(0.613, 0.696, 0.002);
        glVertex3f(0.564, 0.691, 0.002);
        glVertex3f(0.513, 0.677, 0.002);
        glVertex3f(0.465, 0.662, 0.002);
        glVertex3f(0.417, 0.640, 0.002);
        glVertex3f(0.372, 0.614, 0.002);
        glVertex3f(0.329, 0.578, 0.002);
        glVertex3f(0.295, 0.538, 0.002);
        glVertex3f(0.268, 0.491, 0.002);
        glVertex3f(0.254, 0.443, 0.002);
        glVertex3f(0.251, 0.395, 0.002);
        glVertex3f(0.257, 0.341, 0.002);
        glVertex3f(0.277, 0.297, 0.002);
        glVertex3f(0.307, 0.251, 0.002);
        glVertex3f(0.343, 0.216, 0.002);
        glVertex3f(0.393, 0.181, 0.002);
        glVertex3f(0.444, 0.154, 0.002);
        glVertex3f(0.496, 0.133, 0.002);
        glVertex3f(0.552, 0.118, 0.002);
        glVertex3f(0.604, 0.110, 0.002);
        glVertex3f(0.664, 0.108, 0.002);
        glEnd();

        ///Upper Tail
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);

        glVertex3f(0.378, 0.749, 0.002);
        glVertex3f(0.411, 0.768, 0.002);
        glVertex3f(0.451, 0.780, 0.002);
        glVertex3f(0.514, 0.790, 0.002);
        glVertex3f(0.585, 0.792, 0.002);
        glVertex3f(0.651, 0.788, 0.002);
        glVertex3f(0.728, 0.774, 0.002);
        glVertex3f(0.787, 0.758, 0.002);
        glVertex3f(0.839, 0.739, 0.002);
        glVertex3f(0.886, 0.715, 0.002);
        glVertex3f(0.936, 0.670, 0.002);
        glVertex3f(0.397, 0.627, 0.002);
        glVertex3f(0.367, 0.664, 0.002);
        glVertex3f(0.345, 0.690, 0.002);
        glVertex3f(0.342, 0.710, 0.002);
        glVertex3f(0.353, 0.728, 0.002);
        glEnd();

        ///EYE-1 Front Eye
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(1.068, 0.413, 0.0023);
        glVertex3f(1.094, 0.428, 0.0023);
        glVertex3f(1.112, 0.454, 0.0023);
        glVertex3f(1.116, 0.484, 0.0023);
        glVertex3f(1.102, 0.515, 0.0023);
        glVertex3f(1.075, 0.537, 0.0023);
        glVertex3f(1.044, 0.548, 0.0023);
        glVertex3f(1.003, 0.552, 0.0023);
        glVertex3f(0.972, 0.548, 0.0023);
        glVertex3f(0.936, 0.530, 0.0023);
        glVertex3f(0.912, 0.509, 0.0023);
        glVertex3f(0.902, 0.489, 0.0023);
        glVertex3f(0.903, 0.459, 0.0023);
        glVertex3f(0.921, 0.431, 0.0023);
        glVertex3f(0.951, 0.411, 0.0023);
        glVertex3f(0.987, 0.401, 0.0023);
        glVertex3f(1.024, 0.398, 0.0023);
        glVertex3f(1.049, 0.408, 0.0023);
        glEnd();
        ///Eye-1 Inside
        glColor3ub(110, 191, 234);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(1.007, 0.440, 0.0025);
        glVertex3f(1.032, 0.447, 0.0025);
        glVertex3f(1.047, 0.462, 0.0025);
        glVertex3f(1.052, 0.484, 0.0025);
        glVertex3f(1.036, 0.501, 0.0025);
        glVertex3f(1.012, 0.507, 0.0025);
        glVertex3f(0.987, 0.505, 0.0025);
        glVertex3f(0.968, 0.494, 0.0025);
        glVertex3f(0.958, 0.476, 0.0025);
        glVertex3f(0.967, 0.456, 0.0025);
        glVertex3f(0.988, 0.444, 0.0025);
        glEnd();

        ///EYE-2 Back Eye
        glPushMatrix();
        glTranslatef(-0.250, 0.010, 0.0f);
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(1.068, 0.413, 0.0023);
        glVertex3f(1.094, 0.428, 0.0023);
        glVertex3f(1.112, 0.454, 0.0023);
        glVertex3f(1.116, 0.484, 0.0023);
        glVertex3f(1.102, 0.515, 0.0023);
        glVertex3f(1.075, 0.537, 0.0023);
        glVertex3f(1.044, 0.548, 0.0023);
        glVertex3f(1.003, 0.552, 0.0023);
        glVertex3f(0.972, 0.548, 0.0023);
        glVertex3f(0.936, 0.530, 0.0023);
        glVertex3f(0.912, 0.509, 0.0023);
        glVertex3f(0.902, 0.489, 0.0023);
        glVertex3f(0.903, 0.459, 0.0023);
        glVertex3f(0.921, 0.431, 0.0023);
        glVertex3f(0.951, 0.411, 0.0023);
        glVertex3f(0.987, 0.401, 0.0023);
        glVertex3f(1.024, 0.398, 0.0023);
        glVertex3f(1.049, 0.408, 0.0023);
        glEnd();
        ///Eye-2 Inside
        glColor3ub(110, 191, 234);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(1.007, 0.440, 0.0025);
        glVertex3f(1.032, 0.447, 0.0025);
        glVertex3f(1.047, 0.462, 0.0025);
        glVertex3f(1.052, 0.484, 0.0025);
        glVertex3f(1.036, 0.501, 0.0025);
        glVertex3f(1.012, 0.507, 0.0025);
        glVertex3f(0.987, 0.505, 0.0025);
        glVertex3f(0.968, 0.494, 0.0025);
        glVertex3f(0.958, 0.476, 0.0025);
        glVertex3f(0.967, 0.456, 0.0025);
        glVertex3f(0.988, 0.444, 0.0025);
        glEnd();

        glPopMatrix();
        ///Mouth
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.844, 0.219, 0.0025);
        glVertex3f(0.813, 0.227, 0.0025);
        glVertex3f(0.781, 0.243, 0.0025);
        glVertex3f(0.757, 0.262, 0.0025);
        glVertex3f(0.740, 0.288, 0.0025);
        glVertex3f(0.736, 0.325, 0.0025);
        glVertex3f(0.764, 0.309, 0.0025);
        glVertex3f(0.801, 0.294, 0.0025);
        glVertex3f(0.842, 0.286, 0.0025);
        glVertex3f(0.887, 0.281, 0.0025);
        glVertex3f(0.933, 0.279, 0.0025);
        glVertex3f(0.975, 0.288, 0.0025);
        glVertex3f(0.994, 0.290, 0.0025);
        glVertex3f(0.974, 0.262, 0.0025);
        glVertex3f(0.945, 0.239, 0.0025);
        glVertex3f(0.916, 0.224, 0.0025);
        glVertex3f(0.889, 0.216, 0.0025);
        glVertex3f(0.868, 0.216, 0.0025);
        glEnd();

        ///Down Tail-1
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.829, 0.114, 0.002);
        glVertex3f(0.813, 0.029, 0.002);
        glVertex3f(0.794, 0.015, 0.002);
        glVertex3f(0.767, 0.005, 0.002);
        glVertex3f(0.735, 0.010, 0.002);
        glVertex3f(0.713, 0.022, 0.002);
        glVertex3f(0.700, 0.044, 0.002);
        glVertex3f(0.735, 0.107, 0.002);
        glEnd();
        ///Down Tail-2
        //glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(0.617, 0.110, 0.002);
        glVertex3f(0.552, 0.029, 0.002);
        glVertex3f(0.524, 0.022, 0.002);
        glVertex3f(0.494, 0.023, 0.002);
        glVertex3f(0.471, 0.038, 0.002);
        glVertex3f(0.458, 0.061, 0.002);
        glVertex3f(0.462, 0.082, 0.002);
        glVertex3f(0.528, 0.128, 0.002);
        glEnd();

        ///Tail
        glBegin(GL_POLYGON);
        glVertex3f(0.309, 0.253, 0.002);
        glVertex3f(0.100, 0.144, 0.002);
        glVertex3f(0.058, 0.218, 0.002);
        glVertex3f(0.180, 0.381, 0.002);
        glVertex3f(0.070, 0.443, 0.002);
        glVertex3f(0.120, 0.545, 0.002);
        glVertex3f(0.274, 0.486, 0.002);
        glEnd();
        glPopMatrix();
    }

    void Special_APP_R2L()
    {
        glPushMatrix();
        glTranslatef(0.5, -0.5, 0.002);
        glScalef(.7, .7, 1);
        ///SpecialFish_1
        ///Body
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.715, 0.106, 0.002);
        glVertex3f(-0.773, 0.108, 0.002);
        glVertex3f(-0.824, 0.114, 0.002);
        glVertex3f(-0.868, 0.122, 0.002);
        glVertex3f(-0.911, 0.132, 0.002);
        glVertex3f(-0.951, 0.145, 0.002);
        glVertex3f(-0.985, 0.159, 0.002);
        glVertex3f(-1.023, 0.175, 0.002);
        glVertex3f(-1.053, 0.194, 0.002);
        glVertex3f(-1.081, 0.215, 0.002);
        glVertex3f(-1.105, 0.237, 0.002);
        glVertex3f(-1.132, 0.262, 0.002);
        glVertex3f(-1.151, 0.296, 0.002);
        glVertex3f(-1.170, 0.323, 0.002);
        glVertex3f(-1.184, 0.363, 0.002);
        glVertex3f(-1.189, 0.406, 0.002);
        glVertex3f(-1.188, 0.447, 0.002);
        glVertex3f(-1.173, 0.495, 0.002);
        glVertex3f(-1.148, 0.540, 0.002);
        glVertex3f(-1.117, 0.573, 0.002);
        glVertex3f(-1.075, 0.606, 0.002);
        glVertex3f(-1.027, 0.635, 0.002);
        glVertex3f(-0.955, 0.664, 0.002);
        glVertex3f(-0.899, 0.680, 0.002);
        glVertex3f(-0.844, 0.691, 0.002);
        glVertex3f(-0.783, 0.697, 0.002);
        glVertex3f(-0.725, 0.701, 0.002);
        glVertex3f(-0.655, 0.701, 0.002);
        glVertex3f(-0.613, 0.696, 0.002);
        glVertex3f(-0.564, 0.691, 0.002);
        glVertex3f(-0.513, 0.677, 0.002);
        glVertex3f(-0.465, 0.662, 0.002);
        glVertex3f(-0.417, 0.640, 0.002);
        glVertex3f(-0.372, 0.614, 0.002);
        glVertex3f(-0.329, 0.578, 0.002);
        glVertex3f(-0.295, 0.538, 0.002);
        glVertex3f(-0.268, 0.491, 0.002);
        glVertex3f(-0.254, 0.443, 0.002);
        glVertex3f(-0.251, 0.395, 0.002);
        glVertex3f(-0.257, 0.341, 0.002);
        glVertex3f(-0.277, 0.297, 0.002);
        glVertex3f(-0.307, 0.251, 0.002);
        glVertex3f(-0.343, 0.216, 0.002);
        glVertex3f(-0.393, 0.181, 0.002);
        glVertex3f(-0.444, 0.154, 0.002);
        glVertex3f(-0.496, 0.133, 0.002);
        glVertex3f(-0.552, 0.118, 0.002);
        glVertex3f(-0.604, 0.110, 0.002);
        glVertex3f(-0.664, 0.108, 0.002);
        glEnd();

        ///Upper Tail
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);

        glVertex3f(-0.378, 0.749, 0.002);
        glVertex3f(-0.411, 0.768, 0.002);
        glVertex3f(-0.451, 0.780, 0.002);
        glVertex3f(-0.514, 0.790, 0.002);
        glVertex3f(-0.585, 0.792, 0.002);
        glVertex3f(-0.651, 0.788, 0.002);
        glVertex3f(-0.728, 0.774, 0.002);
        glVertex3f(-0.787, 0.758, 0.002);
        glVertex3f(-0.839, 0.739, 0.002);
        glVertex3f(-0.886, 0.715, 0.002);
        glVertex3f(-0.936, 0.670, 0.002);
        glVertex3f(-0.397, 0.627, 0.002);
        glVertex3f(-0.367, 0.664, 0.002);
        glVertex3f(-0.345, 0.690, 0.002);
        glVertex3f(-0.342, 0.710, 0.002);
        glVertex3f(-0.353, 0.728, 0.002);
        glEnd();

        ///EYE-1 Front Eye
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-1.068, 0.413, 0.0023);
        glVertex3f(-1.094, 0.428, 0.0023);
        glVertex3f(-1.112, 0.454, 0.0023);
        glVertex3f(-1.116, 0.484, 0.0023);
        glVertex3f(-1.102, 0.515, 0.0023);
        glVertex3f(-1.075, 0.537, 0.0023);
        glVertex3f(-1.044, 0.548, 0.0023);
        glVertex3f(-1.003, 0.552, 0.0023);
        glVertex3f(-0.972, 0.548, 0.0023);
        glVertex3f(-0.936, 0.530, 0.0023);
        glVertex3f(-0.912, 0.509, 0.0023);
        glVertex3f(-0.902, 0.489, 0.0023);
        glVertex3f(-0.903, 0.459, 0.0023);
        glVertex3f(-0.921, 0.431, 0.0023);
        glVertex3f(-0.951, 0.411, 0.0023);
        glVertex3f(-0.987, 0.401, 0.0023);
        glVertex3f(-1.024, 0.398, 0.0023);
        glVertex3f(-1.049, 0.408, 0.0023);
        glEnd();
        ///Eye-1 Inside
        glColor3ub(110, 191, 234);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-1.007, 0.440, 0.0025);
        glVertex3f(-1.032, 0.447, 0.0025);
        glVertex3f(-1.047, 0.462, 0.0025);
        glVertex3f(-1.052, 0.484, 0.0025);
        glVertex3f(-1.036, 0.501, 0.0025);
        glVertex3f(-1.012, 0.507, 0.0025);
        glVertex3f(-0.987, 0.505, 0.0025);
        glVertex3f(-0.968, 0.494, 0.0025);
        glVertex3f(-0.958, 0.476, 0.0025);
        glVertex3f(-0.967, 0.456, 0.0025);
        glVertex3f(-0.988, 0.444, 0.0025);
        glEnd();

        ///EYE-2 Back Eye
        glPushMatrix();
        glTranslatef(0.250, 0.010, 0.0f);
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-1.068, 0.413, 0.0023);
        glVertex3f(-1.094, 0.428, 0.0023);
        glVertex3f(-1.112, 0.454, 0.0023);
        glVertex3f(-1.116, 0.484, 0.0023);
        glVertex3f(-1.102, 0.515, 0.0023);
        glVertex3f(-1.075, 0.537, 0.0023);
        glVertex3f(-1.044, 0.548, 0.0023);
        glVertex3f(-1.003, 0.552, 0.0023);
        glVertex3f(-0.972, 0.548, 0.0023);
        glVertex3f(-0.936, 0.530, 0.0023);
        glVertex3f(-0.912, 0.509, 0.0023);
        glVertex3f(-0.902, 0.489, 0.0023);
        glVertex3f(-0.903, 0.459, 0.0023);
        glVertex3f(-0.921, 0.431, 0.0023);
        glVertex3f(-0.951, 0.411, 0.0023);
        glVertex3f(-0.987, 0.401, 0.0023);
        glVertex3f(-1.024, 0.398, 0.0023);
        glVertex3f(-1.049, 0.408, 0.0023);
        glEnd();
        ///Eye-2 Inside
        glColor3ub(110, 191, 234);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-1.007, 0.440, 0.0025);
        glVertex3f(-1.032, 0.447, 0.0025);
        glVertex3f(-1.047, 0.462, 0.0025);
        glVertex3f(-1.052, 0.484, 0.0025);
        glVertex3f(-1.036, 0.501, 0.0025);
        glVertex3f(-1.012, 0.507, 0.0025);
        glVertex3f(-0.987, 0.505, 0.0025);
        glVertex3f(-0.968, 0.494, 0.0025);
        glVertex3f(-0.958, 0.476, 0.0025);
        glVertex3f(-0.967, 0.456, 0.0025);
        glVertex3f(-0.988, 0.444, 0.0025);
        glEnd();

        glPopMatrix();
        ///Mouth
        glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.844, 0.219, 0.0025);
        glVertex3f(-0.813, 0.227, 0.0025);
        glVertex3f(-0.781, 0.243, 0.0025);
        glVertex3f(-0.757, 0.262, 0.0025);
        glVertex3f(-0.740, 0.288, 0.0025);
        glVertex3f(-0.736, 0.325, 0.0025);
        glVertex3f(-0.764, 0.309, 0.0025);
        glVertex3f(-0.801, 0.294, 0.0025);
        glVertex3f(-0.842, 0.286, 0.0025);
        glVertex3f(-0.887, 0.281, 0.0025);
        glVertex3f(-0.933, 0.279, 0.0025);
        glVertex3f(-0.975, 0.288, 0.0025);
        glVertex3f(-0.994, 0.290, 0.0025);
        glVertex3f(-0.974, 0.262, 0.0025);
        glVertex3f(-0.945, 0.239, 0.0025);
        glVertex3f(-0.916, 0.224, 0.0025);
        glVertex3f(-0.889, 0.216, 0.0025);
        glVertex3f(-0.868, 0.216, 0.0025);
        glEnd();

        ///Down Tail-1
        glColor3ub(233, 249, 9);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.829, 0.114, 0.002);
        glVertex3f(-0.813, 0.029, 0.002);
        glVertex3f(-0.794, 0.015, 0.002);
        glVertex3f(-0.767, 0.005, 0.002);
        glVertex3f(-0.735, 0.010, 0.002);
        glVertex3f(-0.713, 0.022, 0.002);
        glVertex3f(-0.700, 0.044, 0.002);
        glVertex3f(-0.735, 0.107, 0.002);
        glEnd();
        ///Down Tail-2
        //glColor3ub(255, 255, 255);//(R,G,B)
        glBegin(GL_POLYGON);
        glVertex3f(-0.617, 0.110, 0.002);
        glVertex3f(-0.552, 0.029, 0.002);
        glVertex3f(-0.524, 0.022, 0.002);
        glVertex3f(-0.494, 0.023, 0.002);
        glVertex3f(-0.471, 0.038, 0.002);
        glVertex3f(-0.458, 0.061, 0.002);
        glVertex3f(-0.462, 0.082, 0.002);
        glVertex3f(-0.528, 0.128, 0.002);
        glEnd();

        ///Tail
        glBegin(GL_POLYGON);
        glVertex3f(-0.309, 0.253, 0.002);
        glVertex3f(-0.100, 0.144, 0.002);
        glVertex3f(-0.058, 0.218, 0.002);
        glVertex3f(-0.180, 0.381, 0.002);
        glVertex3f(-0.070, 0.443, 0.002);
        glVertex3f(-0.120, 0.545, 0.002);
        glVertex3f(-0.274, 0.486, 0.002);
        glEnd();
        glPopMatrix();
    }

public:
    static const int LEFT2RIGHT = 100;
    static const int RIGHT2LEFT = 200;
    int Food_Value = 1;

    static const int CATEGORY_NORMAL = 50;
    static const int CATEGORY_SPECIAL = 55;
    static const int CATEGORY_BOMB = 60;

    double t = 0.0;

    int ALIGN = LEFT2RIGHT;
    int FOOD_CATEGORY = CATEGORY_NORMAL;

    Food()
    {
        int randomNum = rand()%2000+1;
        if(randomNum%2 == 0)
        {
            ALIGN = RIGHT2LEFT;
            for(int i=0;i<3;i++)
            {
                ctrlPointsX[i] = R2LX[i];
                ctrlPointsY[i] = R2LY[i];
            }
        } else
        {
            ALIGN = LEFT2RIGHT;
            for(int i=0;i<3;i++)
            {
                ctrlPointsX[i] = L2RX[i];
                ctrlPointsY[i] = L2RY[i];
            }
        }

    }
    ~Food()
    {
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
            t += foodSpeed;
        }

    }
    void drawfood()
    {
        if(ALIGN == LEFT2RIGHT)
        {
            ///left to rignt
            glPushMatrix();
            glTranslatef(xval, yval, 0.002);
            glRotatef((-90*t),0,0,1);
            if(FOOD_CATEGORY == CATEGORY_BOMB)
            {
                BombL2R();
            }
            else if(FOOD_CATEGORY == CATEGORY_SPECIAL)
            {
                Special_APP_L2R();
            }
            else
            {
                NormFoodL2R();
            }

            glPopMatrix();
        }
        else
        {
            ///right to left
            glPushMatrix();
            glTranslatef(xval, yval, 0.002);
            glRotatef((90*t),0,0,1);
            if(FOOD_CATEGORY == CATEGORY_BOMB)
            {
                BombR2L();
            }
            else if(FOOD_CATEGORY == CATEGORY_SPECIAL)
            {
                Special_APP_R2L();
            }
            else
            {
                NormFoodR2L();
            }
            glPopMatrix();
        }
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
        STATUS = ALIVE; ///life status
        MOUTH_STATUS = MOUTH_CLOSE; ///mouth status
    }
    ~Cat()
    {
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
                glVertex3f(0.76, 0.92, 0.002);
                glVertex3f(0.68, 1.08, 0.002);
                glVertex3f(0.8, 1.12, 0.002);
                glVertex3f(0.96, 1.12, 0.002);
                glVertex3f(1.08, 1.08, 0.002);
                glVertex3f(1, 0.92, 0.002);
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
                glVertex3f(0.836, 0.988, 0.002);
                glVertex3f(0.864, 0.988, 0.002);
                glVertex3f(0.904, 1.048, 0.002);
                glVertex3f(0.892, 1.072, 0.002);

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
                glVertex3f(0.46, 1.34, 0.001);
                glVertex3f(0.84, 1.34, 0.001);
                glVertex3f(0.84, 1.32, 0.001);
                glVertex3f(0.46, 1.32, 0.001);

                glVertex3f(0.84, 1.232, 0.001);
                glVertex3f(0.812, 1.232, 0.001);
                glVertex3f(0.812, 1.32, 0.001);
                glVertex3f(0.84, 1.32, 0.001);

                glVertex3f(0.46, 1.232, 0.001);
                glVertex3f(0.488, 1.232, 0.001);
                glVertex3f(0.488, 1.32, 0.001);
                glVertex3f(0.46, 1.32, 0.001);

                glVertex3f(0.46, 1.232, 0.001);
                glVertex3f(0.56, 1.152, 0.001);
                glVertex3f(0.56, 1.18, 0.001);
                glVertex3f(0.488, 1.232, 0.001);

                glVertex3f(0.812, 1.232, 0.001);
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
                glVertex3f(0.972, 1.34, 0.001);
                glVertex3f(1.352, 1.34, 0.001);
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
                glVertex3f(1, 1.232, 0.001);

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


