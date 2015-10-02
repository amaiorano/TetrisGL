// TMBlockFactory.h: interface for the TMBlockFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TMBLOCK_FACTORY_H_
#define _TMBLOCK_FACTORY_H_

#include "TMBlock.h"

class TMBlockFactory  
{
	public:		
		TMBlockFactory();
		~TMBlockFactory();

		TMBlock GetRandomBlock();			// Returns a copy of the block
		TMBlock* GetBlockWithId(int id);	// Returns actual block

	private:
		TMBlock m_allBlocksArray[7];
};

#endif _TMBLOCK_FACTORY_H_
