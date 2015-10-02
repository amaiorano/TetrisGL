// TMBlock.h: interface for the TMBlock class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TMBLOCK_H_
#define _TMBLOCK_H_

#include "Defs.h"

#define ON_MAP	-1

class TMMap;

// Represents a single Tetris block (made up of 4 squares)
class TMBlock  
{
	public:		
		TMBlock();
		~TMBlock();

		inline void SetId(UCHAR id);
		inline void SetMapPosition(char row, char col);
		inline void SetSize(UCHAR size);
		inline void SetSpecialRotate();


		void SetShape(	char r1[4] = "0000",
						char r2[4] = "0000",
						char r3[4] = "0000",
						char r4[4] = "0000" );

		void Draw(int x=ON_MAP, int y=ON_MAP);	// Draws the block, default position is on the map
		void DrawSquare(int x, int y);			// Draws a square at (x,y) on the screen		

		// Functions to move the block on the map
		bool MoveDown();	// Returns true if the block has been placed on the map
		void MoveLeft();
		void MoveRight();
		
		void RotateLeft();
		void RotateRight();

		bool BlockCanFitOnMap();

		// Accessors
		inline UCHAR GetId();

	private:
		void RotateSpecial();		// Performs special rotation
		void DoRotateLeft();		// Performs the left rotation
		void DoRotateRight();		// Performs the right rotation

		static TMMap* m_pMap;		// Static pointer to the map object		

		UCHAR m_id;					// Id of this block (must be >0)
		char m_mapRow, m_mapCol;	// Position on the TMMap
		UCHAR m_size;				// The max size of the block (2, 3, or 4)
		char m_shape[4][4];			// Defines the shape of the block

		char m_rotShape[4][4];		// Used to perform rotations

		bool m_specialRotate;		// If true, block rotates left,right,left,right only
		bool m_specialRotLeft;		// Used to toggle special rotation direction
};


// Inline function definitions

inline void TMBlock::SetId(UCHAR id)
{
	ASSERT(id>0, "Bad block id");
	m_id = id;
}

inline void TMBlock::SetMapPosition(char row, char col)
{
	ASSERT(row>=0 && row<MAP_ROWS && row>=0 && col<MAP_COLS, "Bad map position for block");

	m_mapRow = row;
	m_mapCol = col;
}

inline void TMBlock::SetSize(UCHAR size)
{
	ASSERT(size==2 || size==3 || size==4, "Invalid block size");
	m_size = size;
}

inline void TMBlock::SetSpecialRotate()
{
	m_specialRotate = true;
}

inline UCHAR TMBlock::GetId()
{
	return m_id;
}

#endif _TMBLOCK_H_
