#include "ofxLibMini.h"
#define VIEWER_WINWIDTH 1024
#define VIEWER_WINHEIGHT 512
#define VIEWER_FPS 25.0f

ofxLibMini::ofxLibMini()
{
    //ctor
}

ofxLibMini::~ofxLibMini()
{
    //dtor
}
 miniview *viewer = new miniview();

// the camera object
static minicam *cam=NULL;

// the viewing parameters
static miniscene::MINISCENE_PARAMS *params=NULL;

// the earth parameters
static miniearth::MINIEARTH_PARAMS *eparams=NULL;

// the terrain parameters
static miniterrain::MINITERRAIN_PARAMS *tparams=NULL;

// eye point deltas
static double dez,aez;

// viewing angle deltas
static double turn,incline;

// gliding speed
static double speed,topspeed;

// gliding parameters
static double minspeed=VIEWER_MINSPEED,maxspeed=VIEWER_MAXSPEED,speedinc=0.1,accel=0.1,gravity=0.0,hover=VIEWER_HOVER;

// wakeup flag
static BOOLINT wakeup=TRUE;

// command line switches
static int sw_stereo=0;
static int sw_anaglyph=0;
static int sw_full=0;
static int sw_multi=0;
static int sw_reset=0;
static int sw_autos3tc=0;
static int sw_bricks=0;
static int sw_mpass=0;

// initialize the view point
void initview(minicoord e,double a,double p,double dh=0.0)
   {
   //initwindow(winwidth,winheight);

   cam->set_eye(e,a,p);

   cam->move_down(-dh);
   cam->move_above(hover);

   viewer->initeyepoint(cam->get_eye());

   dez=aez=0.0;
   turn=incline=0.0;
   speed=topspeed=0.0;
   }

// the terrain parameters
static // load settings
void loadsettings()
   {
   minilayer *ref;
   char *savname;

   FILE *file;

   miniv3f e;
   int type;

   float a,p;

   miniscene::MINISCENE_PARAMS prms;
   miniearth::MINIEARTH_PARAMS eprms;
   miniterrain::MINITERRAIN_PARAMS tprms;

   int flag;

   initview(viewer->getinitial(),0.0,-VIEWER_FOVY/3,VIEWER_UPLIFT);

   ref=viewer->getearth()->getreference();
   if (ref!=NULL) savname=ref->getcache()->getfile(VIEWER_SAVFILE);
   else savname=strdup(VIEWER_SAVFILE);

   if (savname!=NULL)
      {
      viewer->get(prms);
      viewer->getearth()->get(eprms);
      viewer->getearth()->getterrain()->get(tprms);

      if ((file=fopen(savname,"rb"))==NULL)
         {
         free(savname);
         return;
         }

      free(savname);

      // load essential parameters:

      if (fscanf(file,"ex=%f\n",&e.x)!=1) ERRORMSG();
      if (fscanf(file,"ey=%f\n",&e.y)!=1) ERRORMSG();
      if (fscanf(file,"ez=%f\n",&e.z)!=1) ERRORMSG();

      if (fscanf(file,"type=%d\n",&type)!=1) ERRORMSG();

      if (fscanf(file,"angle=%f\n",&a)!=1) ERRORMSG();
      if (fscanf(file,"pitch=%f\n",&p)!=1) ERRORMSG();

      if (fscanf(file,"farp=%f\n",&prms.farp)!=1) ERRORMSG();
      if (fscanf(file,"relres=%f\n",&tprms.relres1)!=1) ERRORMSG();
      if (fscanf(file,"relrange=%f\n",&tprms.relrange1)!=1) ERRORMSG();

      if (fscanf(file,"fovy=%f\n",&prms.fovy)!=1) ERRORMSG();

      if (fscanf(file,"sealevel=%g\n",&tprms.sealevel)!=1) ERRORMSG();
      if (tprms.sealevel<-MAXFLOAT/2) tprms.sealevel=-MAXFLOAT;

      // load optional parameters:

      if (fscanf(file,"usefog=%d\n",&flag)!=1) ERRORMSG();
      eprms.usefog=flag;

      if (fscanf(file,"usecontours=%d\n",&flag)!=1) ERRORMSG();
      eprms.usecontours=flag;

      if (fscanf(file,"usebathymap=%d\n",&flag)!=1) ERRORMSG();
      eprms.usebathymap=flag;

      if (fscanf(file,"useskydome=%d\n",&flag)!=1) ERRORMSG();
      eprms.useskydome=flag;

      if (fscanf(file,"usewaypoints=%d\n",&flag)!=1) ERRORMSG();
      eprms.usewaypoints=flag;

      if (fscanf(file,"usebricks=%d\n",&flag)!=1) ERRORMSG();
      eprms.usebricks=flag;

      if (fscanf(file,"fogdensity=%f\n",&eprms.fogdensity)!=1) ERRORMSG();

      fclose(file);

      viewer->getearth()->getterrain()->set(tprms);
      viewer->getearth()->set(eprms);
      viewer->set(prms);

      initview(minicoord(miniv4d(e),(minicoord::MINICOORD)type),a,p);
      }
   }



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
    minicoord eye(miniv3d(ex,ey,ez)); // eye point in ECEF
    miniv3d dir(dx,dy,dz); // viewing direction
    miniv3d up(ux,uy,uz); // up vector



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

   tprms.bathywidth=VIEWER_BATHYWIDTH;
   tprms.bathyheight=2;
   tprms.bathycomps=4;


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
    float aspect=1.0f;
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


void ofxLibMini::setup( char filename[MAX_STR]){

    initparams();
    int width=1024,height=512;
    viewer->getearth()->load(filename);

    float aspect=width/height; // aspect ratio of viewing window

    viewer->get()->nearp=10.0; // near clipping plane
    viewer->get()->farp=10000.0; // far clipping plane
    minicoord eye(miniv3d(ex,ey,ez)); // eye point in ECEF
    miniv3d dir(dx,dy,dz); // viewing direction
    miniv3d up(ux,uy,uz); // up vector

    viewer->initeyepoint(eye); //// prefetch data
     // initialize camera
    viewer->propagate();
    cam=new minicam(viewer->getearth());

    // tell actual camera
    viewer->set_camera(cam);
    loadsettings();




}
