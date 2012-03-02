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



   // height field is a float array
    float hfield[]={0,0,0,0,0,
                   0,3,3,3,0,
                   0,3,5,3,0,
                   0,3,3,3,0,
                   0,0,0,0,0};

    int size=5; // grid size

    float dim=5.0f; // cell dimension
    float scale=1.0f; // vertical scaling


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

    void mynotify(int i,int j,int s)
      {
      // optional "notify" callback
      // triggered during quadtree traversal
      // called for each visible node of the quadtree
      // to disable the callback pass the NULL pointer to the ministub
      // (i,j) is the center of the actual node in grid coordinates
      // s is the size of the actual node in grid units

      // only add extra code here if you know what you are doing
      // ...
      }

    float mygetelevation(int i,int j,int S,void *data=NULL)
      {
      // optional "getelevation" callback
      // if image=NULL is passed to the ministub constructor
      // this callback is evaluated separately for each grid point
      // use this for the sequential access of a height field
      // e.g. for memory efficient reading from an input stream
      // as a reference to the calling object an optional
      // data pointer can be passed to the callback

      // return the elevation at grid position (i,j) here
      return(hfield[i+j*S]); // the size of the grid must be equal to SxS
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

    glScalef(dim,scale,-dim); // scale vertices
    glTranslatef(-size/2+cx,cy,-size/2+cz); // translate vertices


    myfancnt=0;

      stub->draw(res,
                 ex,ey,ez,
                 dx,dy,dz,
                 ux,uy,uz,
                 fovy,aspect,
                 nearp,farp);

      glEnd();


    camera.end();
   glutSwapBuffers();
   }





void ofxLibMini::setup(){



   stub=new ministub(hfield,
                        &size,&dim,scale,
                        cellaspect,cx,cy,cz,
                        mybeginfan,myfanvertex,
                        mynotify,
                        mygetelevation,
                        NULL);



}
