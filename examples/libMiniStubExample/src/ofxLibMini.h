#ifndef OFXLIBMINI_H
#define OFXLIBMINI_H


#include "ofMain.h"

#include <mini/minibase.h>
#include <mini/ministub.h>

#include <mini/pnmbase.h>


#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

const int MAX_STR=1024;
class ofxLibMini
{
    public:
        ofxLibMini();
        ~ofxLibMini();

        void setPerspective();
        void loadFile();
        void setup( char pnmfilename[MAX_STR],int width,int height,int components);
        void display();


        int size; // grid size

    protected:
    private:

        float *hfield;
        unsigned char  *data,*ptr;

};

#endif // OFXLIBMINI_H
