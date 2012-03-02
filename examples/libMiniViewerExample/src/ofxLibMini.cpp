#include "ofxLibMini.h"

ofxLibMini::ofxLibMini()
{
    //ctor
}

ofxLibMini::~ofxLibMini()
{
    //dtor
}
 miniview *viewer = new miniview();


// the viewing parameters
static miniscene::MINISCENE_PARAMS *params=NULL;

// the earth parameters
static miniearth::MINIEARTH_PARAMS *eparams=NULL;

// the terrain parameters
static miniterrain::MINITERRAIN_PARAMS *tparams=NULL;



   float dim=5.0f; // cell dimension
   float scale=1.0f; // vertical scaling




   float res=1000.0f;
   float ex=0.0f,ey=10.0f,ez=30.0f;
   float fx=0.0f,fy=10.0f,fz=30.0f;
   float dx=0.0f,dy=-0.25f,dz=-1.0f;
   float ux=0.0f,uy=1.0f,uz=0.0f;
   float fovy=60.0f;
   float aspect=1.0f;


   float cellaspect=1.0f; // cell aspect ratio
   float cx=0.0f,cy=0.0f,cz=0.0f; // grid center
// initialize the viewing parameters
void initparams()
   {
   miniscene::MINISCENE_PARAMS prms;
   miniearth::MINIEARTH_PARAMS eprms;
   miniterrain::MINITERRAIN_PARAMS tprms;

   viewer->get(prms);

   prms.winwidth=VIEWER_WINWIDTH;
   prms.winheight=VIEWER_WINHEIGHT;

   prms.fps=VIEWER_FPS;

   prms.fovy=VIEWER_FOVY;
   prms.nearp=VIEWER_NEARP;
   prms.farp=VIEWER_FARP;

   viewer->set(prms);

   viewer->getearth()->get(eprms);

   eprms.warpmode=WARPMODE_AFFINE_REF;
   eprms.nonlin=TRUE;

   eprms.usefog=TRUE;
   eprms.useshaders=FALSE;
   eprms.usediffuse=FALSE;
   eprms.usedetail=FALSE;
   eprms.usevisshader=TRUE;
   eprms.usebathymap=FALSE;
   eprms.usecontours=FALSE;
   eprms.usenprshader=FALSE;
   eprms.useskydome=FALSE;
   eprms.usewaypoints=TRUE;
   eprms.usebricks=(sw_bricks==0)?FALSE:TRUE;
   eprms.useearth=TRUE;
   eprms.useflat=FALSE;

   eprms.fogstart=VIEWER_FOGSTART;
   eprms.fogend=VIEWER_FOGEND;
   eprms.fogdensity=VIEWER_FOGDENSITY;

   eprms.voidstart=VIEWER_VOIDSTART;
   eprms.abyssstart=VIEWER_ABYSSSTART;

   viewer->getearth()->set(eprms);

   viewer->getearth()->getterrain()->get(tprms);

   tprms.scale=VIEWER_SCALE;
   tprms.exaggeration=VIEWER_EXAGGER;
   tprms.res=VIEWER_RES;
   tprms.relres1=VIEWER_RELRES;
   tprms.range=VIEWER_RANGE;
   tprms.relrange1=VIEWER_RELRANGE;
   tprms.sealevel=VIEWER_SEALEVEL;

   tprms.genmipmaps=TRUE;
   tprms.automipmap=TRUE;

   tprms.autocompress=(sw_autos3tc==0)?FALSE:TRUE;
   tprms.lod0uncompressed=FALSE;

   tprms.contours=VIEWER_CONTOURS;
   tprms.seabottom=VIEWER_SEABOTTOM;

   tprms.bathystart=VIEWER_BATHYSTART;
   tprms.bathyend=VIEWER_BATHYEND;

   tprms.bathymap=VIEWER_BATHYMAP;
   tprms.bathywidth=VIEWER_BATHYWIDTH;
   tprms.bathyheight=2;
   tprms.bathycomps=4;

   tprms.nprbathystart=VIEWER_NPRBATHYSTART;
   tprms.nprbathyend=VIEWER_NPRBATHYEND;

   tprms.nprbathymap=VIEWER_NPRBATHYMAP;
   tprms.nprbathywidth=VIEWER_NPRBATHYWIDTH;
   tprms.nprbathyheight=2;
   tprms.nprbathycomps=4;

   tprms.nprcontours=VIEWER_NPRCONTOURS;

   tprms.signpostheight=VIEWER_SIGNPOSTHEIGHT;
   tprms.signpostrange=VIEWER_SIGNPOSTRANGE;

   tprms.bricksize=VIEWER_BRICKSIZE;
   tprms.brickradius=VIEWER_BRICKRADIUS;

   tprms.brickpasses=(sw_mpass==0)?1:2;
   tprms.brickscroll=VIEWER_BRICKSCROLL;

   viewer->getearth()->getterrain()->set(tprms);
   }


void ofxLibMini::display(){

    BOOLINT stat;

   static int numidle=0;

   stat=viewer->getearth()->checkpending();

   if (stat || wakeup) numidle=0;
   else if (numidle<VIEWER_MAXIDLE) numidle++;

   wakeup=FALSE;

#ifdef VIEWER_MAKESTATIC
   viewer->getearth()->makestatic(numidle>=VIEWER_MAXIDLE);
#else
   viewer->getearth()->freeze(numidle>=VIEWER_MAXIDLE);
#endif

    viewer->clear(); // clear frame buffer
    viewer->cache(eye,dir,up,aspect); // fill vertex cache

    viewer->render_geometry(); // render vertex cache

    glutSwapBuffers();
   }
/*
    minicoord eye(miniv3d(ex,ey,ez)); // eye point in ECEF
    miniv3d dir(dx,dy,dz); // viewing direction
    miniv3d up(ux,uy,uz); // up vector
*/



void ofxLibMini::setup( char filename[MAX_STR]){

    int width=512,height=512;
    viewer->getearth()->load(filename);

    float aspect=width/height; // aspect ratio of viewing window

    viewer->get()->nearp=10.0; // near clipping plane
    viewer->get()->farp=10000.0; // far clipping plane
    minicoord eye(miniv3d(ex,ey,ez)); // eye point in ECEF
    miniv3d dir(dx,dy,dz); // viewing direction
    miniv3d up(ux,uy,uz); // up vector
     //viewer->initeyepoint(cam->get_eye());

    viewer->initeyepoint(eye); //// prefetch data
     // initialize camera
     viewer->propagate();
   cam=new minicam(viewer->getearth());

   // tell actual camera
   viewer->set_camera(cam);




}
