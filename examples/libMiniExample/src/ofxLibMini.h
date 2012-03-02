#ifndef OFXLIBMINI_H
#define OFXLIBMINI_H


#include "ofMain.h"
//#include <mini/mini.h>
//#include <mini/minibase.h>
#include <mini/ministub.h>
//#include <mini/minitime.h>
//#include <mini/minitile.h>


#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif


class ofxLibMini
{
    public:
        ofxLibMini();
        ~ofxLibMini();

        void setPerspective();
        void setup();
        void display();

        //static int winwidth,winheight,winid;
        int winwidth,winheight,winid;

        // minitile *terrain,*layer;
        ofCamera camera;
/*
static int rotmode;
static int posmode;
static int texmode;
static int fogmode;
static int skymode;
*/
    protected:
    private:
};

#endif // OFXLIBMINI_H
