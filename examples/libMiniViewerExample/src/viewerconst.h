#ifndef VIEWERCONST_H
#define VIEWERCONST_H

#define VIEWER_SCALE 100.0f
#define VIEWER_EXAGGER 3.0f

#define VIEWER_FOVY 60.0f
#define VIEWER_NEARP 10.0f
#define VIEWER_FARP 30000.0f

#define VIEWER_RES 1.0E4f
#define VIEWER_RELRES 0.25f
#define VIEWER_RANGE 0.01f
#define VIEWER_RELRANGE 0.25f

#define VIEWER_SEALEVEL -MAXFLOAT

#define VIEWER_LEVELS 5

#define VIEWER_UPLIFT (0.1f*VIEWER_FARP)

#define VIEWER_MINSPEED 5.0f
#define VIEWER_MAXSPEED 10000.0f

#define VIEWER_GRAVITY 9.81f
#define VIEWER_HOVER (3*VIEWER_NEARP)

#define VIEWER_JUMP 1000.0f
#define VIEWER_DAMP 0.5f
#define VIEWER_BOUNCE 10.0f

#define VIEWER_FAST 10.0f
#define VIEWER_BOOST 100.0f
#define VIEWER_SLOW 10.0f

#define VIEWER_ROTATION 0.1f

#define VIEWER_FOGSTART 0.5f
#define VIEWER_FOGEND 1.0f
#define VIEWER_FOGDENSITY 0.5f

#define VIEWER_VOIDSTART 20000.0f
#define VIEWER_ABYSSSTART -500.0f

#define VIEWER_CONTOURS 10.0f

#define VIEWER_SEABOTTOM -10.0f

#define VIEWER_SIGNPOSTHEIGHT 100.0f
#define VIEWER_SIGNPOSTRANGE 0.25f

#define VIEWER_BRICKSIZE 100.0f
#define VIEWER_BRICKRADIUS 1000.0f

#define VIEWER_BRICKSCROLL 0.5f

#define VIEWER_SAVFILE "settings.sav"

#define VIEWER_BATHYSTART 0.0f
#define VIEWER_BATHYEND -10.0f
#define VIEWER_BATHYMID 0.1f

#define VIEWER_BATHYWIDTH 256

#define VIEWER_NPRBATHYSTART 0.0f
#define VIEWER_NPRBATHYEND 1000.0f

#define VIEWER_NPRBATHYWIDTH 1024

#define VIEWER_NPRCONTOURS 50.0f

#define VIEWER_SBASE 10.0f

#define VIEWER_MAXIDLE 10
#define VIEWER_MINDIFF 0.001f

#endif
