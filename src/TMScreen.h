// TMScreen.h: interface for the TMScreen class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TMSCREEN_H_
#define _TMSCREEN_H_

#include "TMMap.h"

// Represents the entire screen. This class is a singleton.
class TMScreen  
{
	public:
		////////////////////////////////////
		// Functions available for main()
		////////////////////////////////////

		static TMScreen* GetInstance();
		~TMScreen();

		bool DoIteration();			// Performs one iteration of the game

		void NewGame();				// Resets everything
		void PauseGame(bool pause);	// Pauses/Unpauses the game
		TMMap* GetMap();			// Returns the one and only map

		bool IsPaused();			// Returns pause state

	private:
		TMScreen();
		static TMScreen* m_pInstance;

		void Draw();				// Draws the entire screen

		TMMap m_map;
		bool m_pause;
};

#endif _TMSCREEN_H_
