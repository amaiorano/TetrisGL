// TMHighScoreMgr.h: interface for high score manager class
//
//////////////////////////////////////////////////////////////////////

#include "Defs.h"

class TMHighScoreMgr
{
	public:
		// Constants
		enum
		{
			MAX_ENTRIES = 10,
			MAX_NAME_LENGTH = 20
		};

		// Member functions
		TMHighScoreMgr();
		
		bool IsHighScore(long score); // Returns true if score is a high score relative to inner table

		void InsertEntry(char name[MAX_NAME_LENGTH+1], long score); // Inserts entry into table

		// Functions to get the entries from the table
		void FirstEntry(); // Resets inner pointer to first entry in the table
		bool GetNextEntry(UCHAR& pos, char name[MAX_NAME_LENGTH+1], long& score); // Return false if no more entries


	private:
		// Private member functions
		UCHAR GetHighScorePos(long score); // Returns index of where to fit the score, else NOT_HIGH_SCORE

		// Privata data members
		UCHAR m_maxEntries;		// Maximum number of high scores
		UCHAR m_numEntries;		// Current number of high scores

		UCHAR m_currEntry;		// Current entry, used to retrieve entries

		struct PlayerInfo
		{
			char name[MAX_NAME_LENGTH+1];	// Player's name
			long score;						// Player's high score

		} m_playerInfo[MAX_ENTRIES]; // Array of PlayerInfo structs		
};