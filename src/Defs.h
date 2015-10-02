// Defs.h

// Contains global standard definitions and macros

#ifndef _DEFS_H_
#define _DEFS_H_

// Standard includes
#include <windows.h>	// Header file for Windows
#include <stdlib.h>		// rand()
#include <stdio.h>		// sprintf()
#include <string.h>		// strlen()
#include <time.h>		// time()
#include <memory.h>		// memcpy()


#include <gl\gl.h>		// Header file for the OpenGL32 library
#include <gl\glu.h>		// Header file for the GLu32 library
#include "gl\glaux.h"	// Header file for the GLaux library

// Tell the compiler to search and link with these libaries
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "glaux.lib" )


// General defines and constants
#define UCHAR				unsigned char

int Power(int x, int y); // Performs x^y (x to the power of y)

// This little piece of code defines the macro ASSERT:
// In DEBUG mode, it pops a message box if the assertion condition is false;
// In RELEASE mode, the assertion is nothing.
#ifdef _DEBUG
	static char assertString[1024];
	#define ASSERT(AssertCondition, Reason)								\
	{																	\
		if (!(AssertCondition))											\
		{																\
			sprintf(assertString, "ASSERTION!\nFile: %s\nLine: %d\nReason: %s", __FILE__, __LINE__, Reason);	\
			MessageBox(NULL, assertString, "ASSERTION", MB_OK | MB_ICONSTOP);	\
		}																\
	}
#else
	#define ASSERT(AssertCondition, Reason)	((void)0)
#endif


// Game-specific
#define SCREEN_WIDTH				800
#define SCREEN_HEIGHT				600

#define APP_NAME					"TetrisGL"

#define BLOCK_SQUARE_SIZE			1

#define DEF_MAX_AUTO_DOWN_TICKS		500
#define AUTO_DOWN_TICKS_DECREMENT	10

#define MAP_ROWS					20+2 /* Add 2 for the two hidden rows above the screen */
#define MAP_COLS					10

#define NO_BLOCK					0

#define NUM_BLOCK_TYPES				7


#endif _DEFS_H_