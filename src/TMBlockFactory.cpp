// TMBlockFactory.cpp: implementation of the TMBlockFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "Defs.h"
#include "TMBlockFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMBlockFactory::TMBlockFactory()
{
	// Set the random seed to the current time
	srand( (unsigned)time(NULL) );

	// Set the ids for the 7 tetris blocks
	for (UCHAR i = 0; i < NUM_BLOCK_TYPES; ++i)
		m_allBlocksArray[i].SetId(i+1);

	// Define the 7 Tetris blocks

	//////////////////////////////////////////
	m_allBlocksArray[0].SetMapPosition(2, 4);
	m_allBlocksArray[0].SetSize(2);
	m_allBlocksArray[0].SetShape(	"11",
									"11");

	//////////////////////////////////////////
	m_allBlocksArray[1].SetMapPosition(1, 3);
	m_allBlocksArray[1].SetSize(3);
	m_allBlocksArray[1].SetShape(	"000",
									"111",
									"100"	);

	//////////////////////////////////////////
	m_allBlocksArray[2].SetMapPosition(1, 3);
	m_allBlocksArray[2].SetSize(3);
	m_allBlocksArray[2].SetShape(	"000",
									"111",
									"001"	);

	//////////////////////////////////////////
	m_allBlocksArray[3].SetMapPosition(1, 3);
	m_allBlocksArray[3].SetSize(3);
	m_allBlocksArray[3].SetShape(	"000",
									"011",
									"110"	);
	m_allBlocksArray[3].SetSpecialRotate();

	//////////////////////////////////////////
	m_allBlocksArray[4].SetMapPosition(1, 3);
	m_allBlocksArray[4].SetSize(3);
	m_allBlocksArray[4].SetShape(	"000",
									"110",
									"011"	);
	m_allBlocksArray[4].SetSpecialRotate();

	//////////////////////////////////////////
	m_allBlocksArray[5].SetMapPosition(1, 3);
	m_allBlocksArray[5].SetSize(3);
	m_allBlocksArray[5].SetShape(	"000",
									"111",
									"010"	);

	//////////////////////////////////////////
	m_allBlocksArray[6].SetMapPosition(0, 3);
	m_allBlocksArray[6].SetSize(4);
	m_allBlocksArray[6].SetShape(	"0000",
									"0000",
									"1111"	);
	m_allBlocksArray[6].SetSpecialRotate();
}

TMBlockFactory::~TMBlockFactory()
{

}

TMBlock TMBlockFactory::GetRandomBlock()
{	
	return m_allBlocksArray[rand()%7];
}

TMBlock* TMBlockFactory::GetBlockWithId(int id)
{
	ASSERT(id>=1 && id<=7, "Bad block id!");

	return &(m_allBlocksArray[id-1]);
}
