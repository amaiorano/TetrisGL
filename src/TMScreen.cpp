// TMScreen.cpp: implementation of the TMScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "TMScreen.h"
#include "Defs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMScreen* TMScreen::m_pInstance = NULL;

TMScreen* TMScreen::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new TMScreen;
	return m_pInstance;
}

TMScreen::TMScreen() : m_map(0, 0), m_pause(false)
{
}

TMScreen::~TMScreen()
{

}

bool TMScreen::DoIteration()
{
	if (m_pause)
		return true;

	// Is the game over?
	if ( m_map.IsGameOver() )
		return false;

	m_map.DoIteration(); // Tell the map to do its work

	Draw(); // Draw the screen

	return true;
}

void TMScreen::NewGame()
{	
	m_map.Reset();		// Reset the map to start all over
}

void TMScreen::Draw()
{
	// Clear the entire screen
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
	glLoadIdentity ();											// Reset the modelview matrix
	
	// Move the scene back along the negative z-axis, and adjust the x and y so it looks good
	glTranslatef(-4.0f, 9.0f, -28.0f);

	// The tetris code was all written assuming that the screen coordinates for the y-axis
	// increases from top to bottom; but in OpenGL, the default y-axis increases from bottom
	// to top, so we rotate the coordinate system 180 degrees around the z-axis and rotate around
	// y (to make sure x-axis is ok) to match the aforementioned assumption.
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);


	// Draw the borders of the map
	int x1, y1;
	m_map.GetCoordsFromMapPosition(0, 0, x1, y1);

	int x2, y2;
	m_map.GetCoordsFromMapPosition(MAP_ROWS, MAP_COLS, x2, y2);

	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x1, y1);
		glVertex2i(x2, y1);
		glVertex2i(x2, y2);
		glVertex2i(x1, y2);
	glEnd();


	// Show next block
	TMBlock nextBlock = m_map.GetNextBlock();

	// Block 1 and 7 don't look nice normally, so place them specially...
	int nextXPos = 12;
	int nextYPos = 5;
	switch (nextBlock.GetId())
	{
		case 1:
			nextBlock.Draw(nextXPos+(BLOCK_SQUARE_SIZE>>1), nextYPos+BLOCK_SQUARE_SIZE);
			break;

		case 7:
			nextBlock.Draw(nextXPos-(BLOCK_SQUARE_SIZE>>1), nextYPos-(BLOCK_SQUARE_SIZE>>1));
			break;

		default:
			nextBlock.Draw(nextXPos, nextYPos);
	}

	// Draw the map itself (if not paused)
	if (!m_pause)
		m_map.Draw();

	// Flush everything in the OpenGL buffer to the screen
	glFlush ();
}

void TMScreen::PauseGame(bool pause)
{
	m_pause = pause;

	if (m_pause)
		Draw();
}

TMMap* TMScreen::GetMap()
{
	return &m_map;
}

bool TMScreen::IsPaused()
{
	return m_pause;
}
