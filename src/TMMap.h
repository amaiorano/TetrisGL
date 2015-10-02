// TMMap.h: interface for the TMMap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TMMAP_H_
#define _TMMAP_H_

#include "Defs.h"
#include "TMBlockFactory.h"
#include "TMBlock.h"

class TMScreen; // Forward declaration for friendship

// Represents the map on which the blocks move
class TMMap  
{
	public:		
		~TMMap();

		////////////////////////////////////
		// Functions available for main()
		////////////////////////////////////

		// Functions to move and rotate the current block (most of these simply forward
		// the calls to m_currBlock, which is why they're inlined)
		bool MoveCurrBlockDown();			// Moves current block down, returns true if it got placed
		inline void MoveCurrBlockLeft();	// Moves current block left
		inline void MoveCurrBlockRight();	// Moves current block right
		inline void RotateCurrBlockLeft();	// Rotates current block left
		inline void RotateCurrBlockRight();	// Rotates current block right

		inline void IncrementScore(long val); // Adds 'val' to the internal score

		inline bool IsGameOver();		// Returns true if the game is over
		inline int GetTotalLines();		// Returns total number of lines made by user so far		
		inline TMBlock GetNextBlock();	// Returns the next block the user will get
		inline long GetScore();			// Returns the current score
		inline int GetCurrLevel();		// Returns the current level

		void Reset();		// Resets all variables for a new game		

	private:
		friend TMScreen; // Following functions accessed by TMScreen

		TMMap(int x, int y); // Constructor takes (x,y) position of the map
		
		bool DoIteration();	// Performs one iteration of the map
		void Draw();		// Draws the map

	private:
		friend TMBlock; // Following functions accessed by TMBlock

	public:
		// This function returns the (x,y) position for the input (row,col) pair
		inline void GetCoordsFromMapPosition(char row, char col, int& x, int &y);
	private:

		// This function returns true if the block can fit on the map at (row,col)
		bool BlockCanFit(char shape[4][4], UCHAR size, char mapRow, char mapCol);

		// This function simply copies the block values into the map grid
		void PlaceBlock(char shape[4][4], UCHAR size, char mapRow, char mapCol, UCHAR id);

		// Checks if any lines are made starting from row to row+size-1,
		// updates m_linesToRemove[] array. Returns true if any lines are to be removed.
		bool CheckForLines(char startRow, UCHAR size);

		void RemoveLines(); // Removes the lines listed in m_linesToRemove[]

	private: // Accessed by TMMap

		bool IsNextLevel();
		void SetNextLevel();	// Puts the game at the next level

		void RemoveLinesEffect1();	// Nice little effect when removing lines

		int m_x, m_y; // Position of the map on the screen

		TMBlockFactory m_blockFactory;
		TMBlock m_currBlock;
		TMBlock m_nextBlock;

		char m_grid[MAP_ROWS][MAP_COLS]; // The grid with all the blocks

		int m_moveDownCurrTicks;	// Determines when to automatically move current block down
		int m_moveDownLastTicks;	// Used with m_moveDownCurrTicks
		int m_moveDownMaxTicks;		// How many ticks must pass before moving the block down

		UCHAR m_linesToRemove[4];	// Max lines we can ever remove are 4
		UCHAR m_numLinesToRemove;	// Number of lines to remove (use with m_lines[])

		bool m_gameOver;

		int m_totalLines;			// Number of lines user has made so far
		long m_score;				// The user's score

		int m_currLevel;			// The current level
};


// Inline function definitions

inline void TMMap::MoveCurrBlockLeft()
{
	m_currBlock.MoveLeft();
}

inline void TMMap::MoveCurrBlockRight()
{
	m_currBlock.MoveRight();
}

inline void TMMap::RotateCurrBlockLeft()
{
	m_currBlock.RotateLeft();
}

inline void TMMap::RotateCurrBlockRight()
{
	m_currBlock.RotateRight();
}

void TMMap::IncrementScore(long val)
{
	m_score += val;
}

inline bool TMMap::IsGameOver()
{
	return m_gameOver;
}

inline int TMMap::GetTotalLines()
{
	return m_totalLines;
}

inline TMBlock TMMap::GetNextBlock()
{
	return m_nextBlock;
}

inline void TMMap::GetCoordsFromMapPosition(char row, char col, int& x, int &y)
{
	x = m_x + (col*BLOCK_SQUARE_SIZE);
	y = m_y + (row*BLOCK_SQUARE_SIZE);

	y -= BLOCK_SQUARE_SIZE<<1; // Take the two invisible top columns into account

//	y = -y;
}

inline long TMMap::GetScore()
{
	return m_score;
}

inline int TMMap::GetCurrLevel()
{
	return m_currLevel;
}

#endif _TMMAP_H_
