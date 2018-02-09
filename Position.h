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
#include "Move.h"

namespace libChess
{
	// forward declatarion
	class Position;
	
	/*! \brief define the state of the board
		\author Marco Belli
		\version 1.0
		\date 27/10/2013
	*/
	class GameState
	{
		friend class Position;
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
		tSquare _epSquare;	/*!<  en passant square*/
		
		unsigned int 
			_fiftyMoveCnt,	/*!<  50 move count used for draw rule*/
			_pliesFromNull,	/*!<  plies from null move*/
		/* todo spostare fuori dal gamestate? */
			_ply;			/*!<  ply from the start*/
			
		bitboardIndex _capturedPiece; /*!<  index of the captured piece for unmakeMove*/
		
		BitMap _checkingSquares[bitboardNumber]; /*!< squares of the board from where a king can be checked*/
		BitMap _hiddenCheckers;	/*!< pieces who can make a discover check moving*/
		BitMap _pinned;	/*!< pinned pieces*/
		BitMap _checkers;	/*!< checking pieces*/
		Move _currentMove;
		
		public:
		
		//-----------------------------------------
		// constructor
		//-----------------------------------------
		GameState(){}
		
		
		//-----------------------------------------
		// getters
		//-----------------------------------------
		const HashKey& getKey()                const { return _key; }
		const HashKey& getPawnKey()            const { return _pawnKey; }
		const HashKey& getMaterialKey()        const { return _materialKey; }
		
		const simdScore& getNonMaterialValue() const { return _nonPawnMaterialValue; }
		const simdScore& getMaterialValue()    const { return _materialValue; }
		
		eTurn getTurn()                        const {return _turn; }
		eCastle getCastleRights()              const {return _castleRights; }
		tSquare getEpSquare()                  const {return _epSquare; }
		
		unsigned int getFiftyMoveCnt()         const { return _fiftyMoveCnt; }
		unsigned int getPliesFromNullCnt()     const { return _pliesFromNull; }
		unsigned int getPliesCnt()             const { return _ply; }
		
		bitboardIndex getCapturedPiece()       const { return _capturedPiece; }
		BitMap getCheckingSquare( const bitboardIndex idx ) const { return _checkingSquares[idx]; }
		
		const BitMap& getHiddenCheckers()      const { return _hiddenCheckers; }
		const BitMap& getPinned()              const { return _pinned; }
		const BitMap& getCheckers()            const { return _checkers; }
		
		const Move& getCurrentMove()           const { return _currentMove; }
		
		protected:
		//-----------------------------------------
		// methods
		//-----------------------------------------
		inline void changeTurn()
		{
			_turn = (eTurn)( blackTurn - _turn );
			_key.changeSide();
		}
		
		inline void setCurrentMove( const Move& m )
		{
			_currentMove = m;
		}
		
		inline void incrementCounters()
		{
			++_ply;
			++_fiftyMoveCnt;
			++_pliesFromNull;
		}
		
		inline void incrementCountersNullMove()
		{
			++_ply;
			++_fiftyMoveCnt;
			_pliesFromNull = 0;
		}
		
		inline void resetFiftyMovecounter()
		{
			_fiftyMoveCnt = 0;
		}
		
		inline void resetEpSquare()
		{
			if( _epSquare != squareNone)
			{
				assert( _epSquare < squareNumber );
				_key.removeEp(_epSquare);
				_epSquare = squareNone;
			}
		}
		
		inline void setEpSquare( const tSquare sq)
		{
			assert( _epSquare == squareNone);
			assert( sq < squareNumber );
			_epSquare = sq;
			_key.addEp(_epSquare);
			
			
		}
		
		inline void setCapturedPiece( const bitboardIndex idx )
		{
			assert( idx < bitboardNumber );
			_capturedPiece = idx;
		}
		inline void resetCapturedPiece()
		{
			_capturedPiece = empty;
		}
		
		inline void updateCastleRights( const int cr )
		{
			const int filteredCR = _castleRights & cr;
			// Update castle rights if needed
			if ( filteredCR )
			{
				assert( ( filteredCR ) < 16 );
				_key.changeCastlingRight( filteredCR );
				_castleRights = (eCastle)( _castleRights & (~filteredCR) );
			}
		}
		
		inline void setPinned( const BitMap& b)
		{
			_pinned = b;
		}
		
	};
	
	class Position
	{
	
	public:
		
		
	private:
		
	};
}


#endif

