#ifndef OFXLIBMINI_H
#define OFXLIBMINI_H


#include "ofMain.h"

#include <mini/minibase.h>
#include <mini/miniv3f.h>
#include <mini/miniv3d.h>
#include <mini/miniOGL.h>

#include <mini/minilod.h>
#include <mini/minilayer.h>
#include <mini/miniterrain.h>
#include <mini/minishader.h>

#include <mini/minitile.h>
#include <mini/minitext.h>

#include <mini/pnmbase.h>


#include <mini/minicam.h>

#include <mini/minipano.h>
//#include <mini/minibrick.h>
#include <mini/miniview.h>



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


        void setup(char filename[MAX_STR]);
        void display();




        // minitile *terrain,*layer;


    protected:
    private:
};

#endif // OFXLIBMINI_H