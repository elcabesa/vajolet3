/*
	This file is part of Vajolet.
	Copyright (C) 2013-2018 Marco Belli
	
    Vajolet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Vajolet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Vajolet.  If not, see <http://www.gnu.org/licenses/>
	
	*Copyright (C) 2007 Pradyumna Kannan.
	*
	*This code is provided 'as-is', without any expressed or implied warranty.
	*In no event will the authors be held liable for any damages arising from
	*the use of this code. Permission is granted to anyone to use this
	*code for any purpose, including commercial applications, and to alter
	*it and redistribute it freely, subject to the following restrictions:
	*
	*1. The origin of this code must not be misrepresented; you must not
	*claim that you wrote the original code. If you use this code in a
	*product, an acknowledgment in the product documentation would be
	*appreciated but is not required.
	*
	*2. Altered source versions must be plainly marked as such, and must not be
	*misrepresented as being the original code.
	*
	*3. This notice may not be removed or altered from any source distribution.
*/

#ifndef MOVESELECTOR_H_
#define MOVESELECTOR_H_

#include "Position.h"
#include "MoveList.h"
#include "MoveGenerator.h"

namespace libChess
{
	
	class MoveSelector
	{
		public:
			/*****************************************************************
			*	constructors
			******************************************************************/
			MoveSelector( const Position& pos );
			/*****************************************************************
			*	Operators
			******************************************************************/
			
			/*****************************************************************
			*	Iterator
			******************************************************************/
			
			/*****************************************************************
			*	methods
			******************************************************************/
			// todo rimuovere
			MoveList< MoveGenerator::maxMovePerPosition >& getMoveList( void );
			/*****************************************************************
			*	static methods
			******************************************************************/
			
			/*****************************************************************
			*	members
			******************************************************************/
		private:
		const Position& _pos;
		MoveList< MoveGenerator::maxMovePerPosition > _ml;
	};
	
	MoveSelector::MoveSelector( const Position& pos ):_pos(pos)
	{	
		MoveGenerator::generateMoves< MoveGenerator::allMg >( _pos, _ml );
	}
	
	MoveList< MoveGenerator::maxMovePerPosition >& MoveSelector::getMoveList( void )
	{
		return _ml;
	}
	
	
	
}

#endif /* MOVESELECTOR_H_ */