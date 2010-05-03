#ifndef INCLUDE_AL_GRAPHICS_CONFIG_H
#define INCLUDE_AL_GRAPHICS_CONFIG_H

#include "system/al_Config.h"

// OpenGL platform-dependent includes

#if defined(__IPHONE_2_0)
	#define AL_GRAPHICS_USE_OPENGLES1
	
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
#endif

#if defined(__IPHONE_3_0)
	#define AL_GRAPHICS_USE_OPENGLES2
	
	#import <OpenGLES/ES2/gl.h>
	#import <OpenGLES/ES2/glext.h>
#endif

#ifdef AL_OSX
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
	#include <OpenGL/glu.h>
	
	#define AL_GRAPHICS_INIT_CONTEXT\
		/* prevents tearing */ \
		{	GLint MacHackVBL = 1;\
			CGLContextObj ctx = CGLGetCurrentContext();\
			CGLSetParameter(ctx,  kCGLCPSwapInterval, &MacHackVBL); }
#endif

#ifdef AL_LINUX
	#include <GL/glew.h>
	#include <GL/gl.h>
	#include <GL/glext.h>
	#include <GL/glu.h>
	#include <time.h>
	
	#define AL_GRAPHICS_INIT_CONTEXT\
		{	GLenum err = glewInit();\
			if (GLEW_OK != err){\
  				/* Problem: glewInit failed, something is seriously wrong. */\
  				fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(err));\
			}\
		}
#endif

#ifdef AL_WIN32
	#include <windows.h>
	#include <gl/gl.h>
	#include <gl/glu.h>
	#pragma comment( lib, "winmm.lib")
	#pragma comment( lib, "opengl32.lib" )
	#pragma comment( lib, "glu32.lib" )
	
	#define AL_GRAPHICS_INIT_CONTEXT

#endif

#endif
