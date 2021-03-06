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
#include "MoveGenerator.h"

namespace libChess
{	
    inline void MoveSelector::_goToNextState()
    {
        _stagedGeneratorState = ( eStagedGeneratorState )( _stagedGeneratorState + 1 );
    }
    
    inline void MoveSelector::_scoreCaptures()
    {
        // todo check whether to change begin of array from begin to actualPosition (inside the list class)
        for( auto & m : *_ml )
        {
            m.setScore( _pos.getMvvLvaScore( m ) );
        }
    }
    
	const Move& MoveSelector::getNextMove()
	{
		while(true)
		{
			switch( _stagedGeneratorState )
			{
				case generateCaptureMoves:
					_ml = new MoveList< maxMovePerPosition >;
					MoveGenerator::generateMoves< MoveGenerator::captureMg >( _pos, *_ml );
					_ml->ignoreMove( _ttMove );
                    
                    _scoreCaptures();

					_goToNextState();
					break;
				case generateCaptureEvasionMoves:
					_ml = new MoveList< maxMovePerPosition >;
					MoveGenerator::generateMoves< MoveGenerator::captureEvasionMg >( _pos, *_ml );
					_ml->ignoreMove( _ttMove );

					// todo readd killer moves
					_scoreCaptures();

					_goToNextState();
					break;
				case generateQuietMoves:
					_ml->reset();
					MoveGenerator::generateMoves< MoveGenerator::quietMg >( _pos, *_ml );
					_ml->ignoreMove( _ttMove );
                    
					_goToNextState();
					
					break;
				case generateQuietEvasionMoves:

					_ml->reset();
					MoveGenerator::generateMoves< MoveGenerator::quietEvasionMg >( _pos, *_ml );
					_ml->ignoreMove( _ttMove );

					//todo readd this line
					//scoreQuietEvasion();
					_goToNextState();
				break;
				
				case iterateCaptureEvasionMoves:
					//todo rifare tutto il codice mancante
					if( const Move& m = _ml->findNextBestMove(); m != Move::NOMOVE )
					{
						return m;
					}
					else
					{
						_goToNextState();
					}
					break;
				case iterateGoodCaptureMoves:
					//todo rifare tutto il codice mancante
					if( const Move& m = _ml->findNextBestMove(); m != Move::NOMOVE )
					{
						return m;
					}
					else
					{
						// todo rimettere _stagedGeneratorState +1 e riunificare i metodi
						_stagedGeneratorState = generateQuietMoves;
					}
					break;
				case iterateQuietEvasionMoves:
				case iterateQuietMoves:
						return _ml->findNextBestMove();
					break;
				case getTT:
				case getTTevasion:
					_goToNextState();

					if( _pos.isMoveLegal( _ttMove ) )
					{
						return _ttMove;
					}
					break;

				default:
					return Move::NOMOVE;
			}
		}
		
		
		// todo  da rimuovere????
		return _ml->findNextBestMove();
	}
}
