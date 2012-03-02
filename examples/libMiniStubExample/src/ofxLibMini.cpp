#include "ofxLibMini.h"

ofxLibMini::ofxLibMini()
{
    //ctor
}

ofxLibMini::~ofxLibMini()
{
    //dtor
}

    ministub *stub;


   float dim=5.0f; // cell dimension
   float scale=0.33f; // vertical scaling


   int myfancnt;

   void mybeginfan()
      {
      // mandatory "beginfan" callback
      // called for each generated triangle fan
      // followed by the vertex callbacks

      if (myfancnt++>0) glEnd();
      glBegin(GL_TRIANGLE_FAN);
      }

   void myfanvertex(float i,float y,float j)
      {
      // mandatory "fanvertex" callback
      // called for each vertex of a triangle fan
      // glVertex3f directly qualifies as a fast "fanvertex" callback
      // (i,j) is the grid coordinate of the vertex
      // y is the unscaled elevation interpolated from the height field
      // these coordinates are transformed by the OpenGL modelview matrix
      // therefore, the real world coordinates of each vertex are
      // (vx,vy,vz)=((i-size/2)*dim+cx,y*scale+cy,(size/2-j)*dim+cz)

      glVertex3f(i,y,j);
      }

   float res=1000.0f;
   float ex=0.0f,ey=10.0f,ez=30.0f;
   float fx=0.0f,fy=10.0f,fz=30.0f;
   float dx=0.0f,dy=-0.25f,dz=-1.0f;
   float ux=0.0f,uy=1.0f,uz=0.0f;
   float fovy=60.0f;
   float aspect=1.0f;
   float nearp=1.0f;
   float farp=100.0f;

   float cellaspect=1.0f; // cell aspect ratio
   float cx=0.0f,cy=0.0f,cz=0.0f; // grid center


void ofxLibMini::display(){


    myfancnt=0;

      stub->draw(res,
                 ex,ey,ez,
                 dx,dy,dz,
                 ux,uy,uz,
                 fovy,aspect,
                 nearp,farp);

      glEnd();


   glutSwapBuffers();
   }




void ofxLibMini::setup( char pnmfilename[MAX_STR],int width,int height,int components){


    data=readPNMfile( pnmfilename,&width,&height,&components);

    if (width!=height) ERRORMSG(); // height field must be quadratic

    short int *hfield=new short int[width*height];

    if (components==1) // 8-bit
      for (int j=0; j<height; j++)
         for (int i=0; i<width; i++)
            hfield[i+j*width]=data[i+(height-1-j)*width];
    else if (components==2) // 16-bit
      for (int j=0; j<height; j++)
         for (int i=0; i<width; i++)
            hfield[i+j*width]=(short int)(256*data[2*(i+(height-1-j)*width)]+data[2*(i+(height-1-j)*width)+1]);
    else ERRORMSG();

    free(data);

    size = 500;
     stub=new ministub(hfield,
                        &size,&dim,scale,
                        cellaspect,cx,cy,cz,
                        mybeginfan,myfanvertex);


delete[] hfield;


}
