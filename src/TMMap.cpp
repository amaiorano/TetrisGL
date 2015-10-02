// TMMap.cpp: implementation of the TMMap class.
//
//////////////////////////////////////////////////////////////////////

#include "TMMap.h"
#include "TMScreen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMMap::TMMap(int x, int y)
	: m_x(x), m_y(y) // The rest of the data members are set in Reset()
{
	ASSERT(x>=0 && x<SCREEN_WIDTH && y>=0 && y<SCREEN_HEIGHT, "Bad map position on screen");
	Reset();
}

TMMap::~TMMap()
{

}

void TMMap::Reset()
{	
	memset(m_grid, NO_BLOCK, sizeof(m_grid));

	m_moveDownMaxTicks = DEF_MAX_AUTO_DOWN_TICKS;	
	m_moveDownLastTicks = GetTickCount();

	m_gameOver = false;

	m_currBlock = m_blockFactory.GetRandomBlock();
	m_nextBlock = m_blockFactory.GetRandomBlock();

	m_totalLines = 0;
	m_score = 0;
	m_currLevel = 0;
}

bool TMMap::DoIteration()
{
	m_moveDownCurrTicks = GetTickCount(); // Grab current ticks

	// If the ticks elapsed has passed the current max ticks, move the block down
	if ( m_moveDownCurrTicks - m_moveDownLastTicks > m_moveDownMaxTicks )
	{
		MoveCurrBlockDown(); // Move the block down

		m_moveDownLastTicks = m_moveDownCurrTicks; // Reset last ticks to current
	}

	return true;
}

void TMMap::Draw()
{
	// Draw the map using the grid
	UCHAR id;
	for (char row=0; row<MAP_ROWS; ++row)
	{
		for (char col=0; col<MAP_COLS; ++col)
		{
			// If there's a block value in the grid, draw it

			id = m_grid[row][col];
			if (id != NO_BLOCK)
			{
				int x, y;
				GetCoordsFromMapPosition(row, col, x, y);
				m_blockFactory.GetBlockWithId(id)->DrawSquare(x, y);
			}
		}
	}	

	// Draw the current block
	m_currBlock.Draw();	
}

bool TMMap::BlockCanFit(char shape[4][4], UCHAR size, char mapRow, char mapCol)
{
	for (char row=0; row<size; ++row)
	{
		for (char col=0; col<size; ++col)
		{			
			if (shape[row][col])
			{
				// If the block is beyond the boundaries of the map, it obviously
				// does not fit
				if (mapRow+row >= MAP_ROWS)
					return false;

				if (mapCol+col<0 || mapCol+col >= MAP_COLS)
					return false;

				// If there's a block value in the grid, then the block can't fit
				if (m_grid[mapRow+row][mapCol+col] != NO_BLOCK)
					return false;
			}
		}
	}

	return true;
}

void TMMap::PlaceBlock(char shape[4][4], UCHAR size, char mapRow, char mapCol, UCHAR id)
{
	for (char row=0; row<size; ++row)
	{
		for (char col=0; col<size; ++col)
		{			
			if (shape[row][col])
			{
				ASSERT(m_grid[mapRow+row][mapCol+col] == NO_BLOCK, "Grid cell not empty!");

				m_grid[mapRow+row][mapCol+col] = id;
			}				
		}
	}
}

bool TMMap::MoveCurrBlockDown()
{
	// Move the current block; if it got placed, then get a new random block
	if ( m_currBlock.MoveDown() ) // Returns true if block was placed
	{
		//m_currBlock = m_blockFactory.GetRandomBlock();
		m_currBlock = m_nextBlock;
		m_nextBlock = m_blockFactory.GetRandomBlock();

		// Does this new block overlap any blocks already on the map?
		if ( !m_currBlock.BlockCanFitOnMap() )
		{
			// Game over!!
			m_gameOver = true;
		}

		return true;
	}

	return false;
}

bool TMMap::CheckForLines(char startRow, UCHAR size)
{
	UCHAR numRows = size; // Number of rows we're going to check
	m_numLinesToRemove = 0; // Reset number of lines

	// Adjust numRows so that row+numRows doesn't go below the map
	if (startRow+numRows >= MAP_ROWS)
		numRows = MAP_ROWS - startRow;

	// Now check the relevant rows
	for (char row=startRow; row<startRow+numRows; ++row)
	{
		// Check if this row is filled with blocks. As soon as
		// we see that it's not, we jump to the next row.
		bool lineInThisRow = true;
		for (int col=0; lineInThisRow && col<MAP_COLS; ++col)
		{
			if (m_grid[row][col] == NO_BLOCK)
				lineInThisRow = false;
		}

		// If this row contains a line of blocks, update m_linesToRemove[]
		if (lineInThisRow)
		{
			m_linesToRemove[m_numLinesToRemove] = row;
			++m_numLinesToRemove;
		}
	}

	return (m_numLinesToRemove > 0);
}

void TMMap::RemoveLines()
{
	RemoveLinesEffect1(); // Perform a nice line removal effect

	// Actually remove the lines from the grid
	for (char i=0; i<m_numLinesToRemove; ++i)
	{
		for (char row=m_linesToRemove[i]; row>0; --row)
			for (char col=0; col<10; ++col)
				m_grid[row][col] = m_grid[row-1][col];
	}

	// Calculate the score based on the lines made and the current level
	// The score is calculated by taking 2 to the power of the number of
	// lines to remove so that making more lines is much more rewarding.
	// We add one to the current level so that level 0 doesn't cancel out
	// the score. And we multiply it all by 10 so that we get a nice '0'
	// as the last value.	
	IncrementScore( 10 * Power(3, m_numLinesToRemove) * (m_currLevel+1) );	

	// Determine if we should go up a level
	if ( IsNextLevel() )
		SetNextLevel();
}

void TMMap::RemoveLinesEffect1()
{
	// No effect coded yet...
}

bool TMMap::IsNextLevel()
{
	// Incremement the number of lines user has made so far
	m_totalLines += m_numLinesToRemove;

	// If we reached the "next level", make it go faster
	if (m_totalLines/10 != m_currLevel)
		return true;

	return false;
}

void TMMap::SetNextLevel()
{
	++m_currLevel; // Increment the current level

	// Now based on the new level, figure out the auto move down ticks amount
	// to make the game go faster

	m_moveDownMaxTicks -= AUTO_DOWN_TICKS_DECREMENT;

	if (m_moveDownMaxTicks < 0)
		m_moveDownMaxTicks = 0;
}
