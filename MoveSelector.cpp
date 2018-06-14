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
*/

#include "MoveSelector.h"

namespace libChess
{
	unsigned int MoveSelector::getNumberOfLegalMoves( void )
	{
		MoveList< MoveGenerator::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( _pos, ml );
		return ml.size();
	}
	
	const Move& MoveSelector::getNextMove()
	{
		while(true)
		{
			switch( _stagedGeneratorState )
			{
				case generateCaptureMoves:
					// todo generate only capture moves!!
					_ml = new MoveList< MoveGenerator::maxMovePerPosition >;
					MoveGenerator::generateMoves< MoveGenerator::allMg >( _pos, *_ml );
					_ml->ignoreMove( _ttMove );

					// todo readd this line
					//scoreCaptureMoves();

					_stagedGeneratorState = ( eStagedGeneratorState )( _stagedGeneratorState + 1 );
					break;
				case iterateGoodCaptureMoves:
					return _ml->findNextBestMove();
					break;
				case getTT:
					_stagedGeneratorState = ( eStagedGeneratorState )( _stagedGeneratorState + 1 );

					if( _pos.isMoveLegal( _ttMove ) )
					{
						return _ttMove;
					}
					break;

				default:
					return Move::NOMOVE;
			}
		}
		
		return _ml->findNextBestMove();
	}
}
