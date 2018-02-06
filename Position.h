/*
	This file is part of Vajolet.

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

#ifndef POSITION_H_
#define POSITION_H_

#include "BitMap.h"
#include "HashKeys.h"
#include "Score.h"

namespace libChess
{
	
	
	
	/*! \brief define the state of the board
		\author Marco Belli
		\version 1.0
		\date 27/10/2013
	*/
	class GameState
	{
		private:
		HashKey 
			_key,		/*!<  hashkey identifying the position*/
			_pawnKey,	/*!<  hashkey identifying the pawn formation*/
			_materialKey;/*!<  hashkey identifying the material signature*/
			
		simdScore _nonPawnMaterialValue; 	/*!< four score used for white/black opening/endgame non pawn material sum*/
		simdScore _materialValue;			/*!< material value of the position*/
		
		/* todo spostare fuori dal gamestate? */
		eTurn _turn;	/*!< who is the active player*/
		eCastle _castleRights; /*!<  actual castle rights*/
		tSquare epSquare;	/*!<  en passant square*/
		
		unsigned int 
			fiftyMoveCnt,	/*!<  50 move count used for draw rule*/
			pliesFromNull,	/*!<  plies from null move*/
		/* todo spostare fuori dal gamestate? */
			ply;			/*!<  ply from the start*/
			
		bitboardIndex _capturedPiece; /*!<  index of the captured piece for unmakeMove*/
		
		BitMap _checkingSquares[bitboardNumber]; /*!< squares of the board from where a king can be checked*/
		BitMap _hiddenCheckersCandidate;	/*!< pieces who can make a discover check moving*/
		BitMap _pinnedPieces;	/*!< pinned pieces*/
		BitMap _checkers;	/*!< checking pieces*/
		Move _currentMove;
		
		public:
		
		GameState(){}
	};
	
	class Position
	{
	
	public:
		
		
	private:
		
	};
}


#endif

