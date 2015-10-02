// TMHighScoreMgr.cpp: implementation for high score manager class
//
//////////////////////////////////////////////////////////////////////

#include "TMHighScoreMgr.h"

#define NOT_HIGH_SCORE		MAX_ENTRIES+5

TMHighScoreMgr::TMHighScoreMgr()
	: m_maxEntries(MAX_ENTRIES), m_numEntries(0), m_currEntry(0)
{
	// Clear up the player info array
	for (int i=0; i<m_maxEntries; ++i)
	{
		memset(m_playerInfo[i].name, 0, sizeof(m_playerInfo[i].name));
		m_playerInfo[i].score = 0L;
	}
}

bool TMHighScoreMgr::IsHighScore(long score)
{
	return ( GetHighScorePos(score) != NOT_HIGH_SCORE );
}

void TMHighScoreMgr::InsertEntry(char name[MAX_NAME_LENGTH+1], long score)
{
	ASSERT(strlen(name), "Name is empty!");
	ASSERT(score > 0, "Score is 0!");

	UCHAR pos = GetHighScorePos(score);
	ASSERT(pos != NOT_HIGH_SCORE, "Not high score!");

	// Insert the player into the table

	// We need to push all scores down by one entry starting from pos down.
	// Crude brute force method, but who cares?

	int i = (m_numEntries==MAX_ENTRIES? MAX_ENTRIES-1 : m_numEntries);
	for ( ; i>pos; --i)
	{
		strcpy(m_playerInfo[i].name, m_playerInfo[i-1].name);	// Overwrite name with entry above
		m_playerInfo[i].score = m_playerInfo[i-1].score;		// Overwrite score with entry above	
	}

	// Now write the new score and name at pos
	strcpy(m_playerInfo[pos].name, name);
	m_playerInfo[pos].score = score;

	if (m_numEntries != MAX_ENTRIES)
		++m_numEntries; // Increment number of entries in the table
}

void TMHighScoreMgr::FirstEntry()
{
	m_currEntry = 0; // Reset current entry index
}

bool TMHighScoreMgr::GetNextEntry(UCHAR& pos, char name[MAX_NAME_LENGTH+1], long& score)
{
	// Are we at the end of the list?
	if (m_currEntry == m_numEntries)
		return false;

	// Copy current entry to output params
	pos = m_currEntry+1; // Add one so that highest score is position 1, not 0
	strcpy(name, m_playerInfo[m_currEntry].name);
	score = m_playerInfo[m_currEntry].score;

	++m_currEntry; // Increment current entry index

	return true;
}


// Private member functions
UCHAR TMHighScoreMgr::GetHighScorePos(long score)
{
	// Don't allow a score of 0 to be considered a high score
	if (score == 0)
		return NOT_HIGH_SCORE;

	// Compare the score to scores in the table
	for (int i=0; i<m_maxEntries; ++i)
	{
		if (score > m_playerInfo[i].score)
			return i;
	}

	return NOT_HIGH_SCORE;
}