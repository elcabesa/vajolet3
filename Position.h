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
		GameState();
		
		
		//-----------------------------------------
		// getters
		//-----------------------------------------
		const HashKey& getKey() const;
		const HashKey& getPawnKey() const;
		const HashKey& getMaterialKey() const;
		
		const simdScore& getNonMaterialValue() const;
		const simdScore& getMaterialValue() const;
		
		eTurn getTurn() const;
		eCastle getCastleRights() const;
		tSquare getEpSquare() const;
		
		unsigned int getFiftyMoveCnt() const;
		unsigned int getPliesFromNullCnt() const;
		unsigned int getPliesCnt() const;
		
		bitboardIndex getCapturedPiece() const;
		BitMap getCheckingSquare( const bitboardIndex idx ) const;
		
		const BitMap& getHiddenCheckers() const;
		const BitMap& getPinned() const;
		const BitMap& getCheckers() const;
		
		const Move& getCurrentMove() const;
		
		protected:
		//-----------------------------------------
		// methods
		//-----------------------------------------
		void setKeys(const HashKey& key, const HashKey& pawnKey, const HashKey& materialKey );
		
		void setMaterialValues(const simdScore MaterialValue, const simdScore nonPawnMaterialValue );
		
		void setTurn( const eTurn turn);
		
		void setCastleRights( const eCastle cr);
		
		void setFiftyMoveCnt( const unsigned int fmc );
		
		void setPliesCnt( const unsigned int cnt );
		
		void changeTurn();
		
		void setCurrentMove( const Move& m );
		
		void incrementCounters();
		
		void incrementCountersNullMove();
		
		void resetFiftyMovecounter();
		
		void resetEpSquare();
		
		void setEpSquare( const tSquare sq);
		
		void setCapturedPiece( const bitboardIndex idx );
		
		void resetCapturedPiece();
		
		void clearCastleRights( const int cr );
		
		void setCheckingSquare( const bitboardIndex idx, const BitMap& b );
		
		void setHiddenChechers( const BitMap& b);
		
		void setPinned( const BitMap& b);
		
		void setCheckers( const BitMap& b );
		
		void keyMovePiece(const bitboardIndex p , const tSquare fromSq, const tSquare toSq);
		
		void keyRemovePiece(const bitboardIndex p , const tSquare sq);
		
		void keyPromotePiece(const bitboardIndex piece, const bitboardIndex promotedPiece, const tSquare sq);
		
		void pawnKeyMovePiece(const bitboardIndex p , const tSquare fromSq, const tSquare toSq);
	
		void pawnKeyRemovePiece(const bitboardIndex p , const tSquare sq);
		
		void materialKeyRemovePiece(const bitboardIndex p , unsigned int count);
	
		void materialKeyPromovePiece(const bitboardIndex piece , const unsigned int count, const bitboardIndex promotedPiece, const unsigned int promotedCount);
		
		void MaterialMovePiece( const simdScore to, const simdScore from );
		
		void MaterialCapturePiece( const simdScore material, const simdScore nonPawnMaterial );
	
		void MaterialPromotePiece( const simdScore material, const simdScore protmotedMaterial , const simdScore nonPawnPromotedMaterial );
		
	};
	
	//-----------------------------------------
	// constructor
	//-----------------------------------------
	inline GameState::GameState(){}
	
	
	//-----------------------------------------
	// getters
	//-----------------------------------------
	inline const HashKey& GameState::getKey()                const { return _key; }
	inline const HashKey& GameState::getPawnKey()            const { return _pawnKey; }
	inline const HashKey& GameState::getMaterialKey()        const { return _materialKey; }
	
	inline const simdScore& GameState::getNonMaterialValue() const { return _nonPawnMaterialValue; }
	inline const simdScore& GameState::getMaterialValue()    const { return _materialValue; }
	
	inline eTurn GameState::getTurn()                        const {return _turn; }
	inline eCastle GameState::getCastleRights()              const {return _castleRights; }
	inline tSquare GameState::getEpSquare()                  const {return _epSquare; }
	
	inline unsigned int GameState::getFiftyMoveCnt()         const { return _fiftyMoveCnt; }
	inline unsigned int GameState::getPliesFromNullCnt()     const { return _pliesFromNull; }
	inline unsigned int GameState::getPliesCnt()             const { return _ply; }
	
	inline bitboardIndex GameState::getCapturedPiece()       const { return _capturedPiece; }
	inline BitMap GameState::getCheckingSquare( const bitboardIndex idx ) const { return _checkingSquares[idx]; }
	
	inline const BitMap& GameState::getHiddenCheckers()      const { return _hiddenCheckers; }
	inline const BitMap& GameState::getPinned()              const { return _pinned; }
	inline const BitMap& GameState::getCheckers()            const { return _checkers; }
	
	inline const Move& GameState::getCurrentMove()           const { return _currentMove; }
	
	//-----------------------------------------
	// methods
	//-----------------------------------------
	inline void GameState::setKeys(const HashKey& key, const HashKey& pawnKey, const HashKey& materialKey )
	{
		_key = key;
		_pawnKey = pawnKey;
		_materialKey = materialKey;
	}
	
	inline void GameState::setMaterialValues(const simdScore materialValue, const simdScore nonPawnMaterialValue )
	{
		_materialValue = materialValue;
		_nonPawnMaterialValue = nonPawnMaterialValue;
	}
	
	inline void GameState::setTurn( const eTurn turn)
	{
		_turn = turn;
	}
	
	inline void GameState::setCastleRights( const eCastle cr)
	{
		_castleRights = cr;
	}
	
	inline void GameState::setFiftyMoveCnt( const unsigned int fmc )
	{
		_fiftyMoveCnt = fmc;
	}
	
	inline void GameState::setPliesCnt( const unsigned int cnt )
	{
		_ply = cnt;
	}
	
	inline void GameState::changeTurn()
	{
		_turn = (eTurn)( blackTurn - _turn );
		_key.changeSide();
	}
	
	inline void GameState::setCurrentMove( const Move& m )
	{
		_currentMove = m;
	}
	
	inline void GameState::incrementCounters()
	{
		++_ply;
		++_fiftyMoveCnt;
		++_pliesFromNull;
	}
	
	inline void GameState::incrementCountersNullMove()
	{
		++_ply;
		++_fiftyMoveCnt;
		_pliesFromNull = 0;
	}
	
	inline void GameState::resetFiftyMovecounter()
	{
		_fiftyMoveCnt = 0;
	}
	
	inline void GameState::resetEpSquare()
	{
		if( _epSquare != squareNone)
		{
			assert( _epSquare < squareNumber );
			_key.removeEp(_epSquare);
			_epSquare = squareNone;
		}
	}
	
	inline void GameState::setEpSquare( const tSquare sq)
	{
		assert( _epSquare == squareNone);
		assert( sq < squareNumber );
		_epSquare = sq;
		_key.addEp(_epSquare);
		
		
	}
	
	inline void GameState::setCapturedPiece( const bitboardIndex idx )
	{
		assert( idx < bitboardNumber );
		_capturedPiece = idx;
	}
	inline void GameState::resetCapturedPiece()
	{
		_capturedPiece = empty;
	}
	
	inline void GameState::clearCastleRights( const int cr )
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
	
	inline void GameState::setPinned( const BitMap& b)
	{
		_pinned = b;
	}

	inline void GameState::setHiddenChechers( const BitMap& b)
	{
		_hiddenCheckers = b;
	}
	
	inline void GameState::setCheckers( const BitMap& b )
	{
		_checkers = b;
	}
	
	inline void GameState::setCheckingSquare( const bitboardIndex idx, const BitMap& b )
	{
		assert( idx < bitboardNumber );
		_checkingSquares[idx] = b;
	}
	
	inline void GameState::keyMovePiece(const bitboardIndex p , const tSquare fromSq, const tSquare toSq)
	{
		_key.movePiece( p, fromSq, toSq );
	}
	
	inline void GameState::keyRemovePiece(const bitboardIndex p , const tSquare sq)
	{
		_key.removePiece( p, sq );
	}
	
	inline void GameState::keyPromotePiece(const bitboardIndex piece, const bitboardIndex promotedPiece, const tSquare sq)
	{
		_key.removePiece( piece, sq).addPiece( promotedPiece, sq);
	}
	
	inline void GameState::pawnKeyMovePiece(const bitboardIndex p , const tSquare fromSq, const tSquare toSq)
	{
		_pawnKey.movePiece( p, fromSq, toSq );
	}
	
	inline void GameState::pawnKeyRemovePiece(const bitboardIndex p , const tSquare sq)
	{
		_pawnKey.removePiece( p, sq );
	}
	
	inline void GameState::materialKeyRemovePiece(const bitboardIndex p , unsigned int count)
	{
		_materialKey.removePiece( p, (tSquare)count );
	}
	
	inline void GameState::materialKeyPromovePiece(const bitboardIndex piece , const unsigned int count, const bitboardIndex promotedPiece, const unsigned int promotedCount)
	{
		_materialKey.removePiece( piece, (tSquare)count ).addPiece( promotedPiece, (tSquare)promotedCount );
	}
	
	inline void  GameState::MaterialMovePiece( const simdScore to, const simdScore from )
	{
		_materialValue += to - from;
	}
	
	inline void  GameState::MaterialCapturePiece( const simdScore material, const simdScore nonPawnMaterial )
	{
		_materialValue -= material;
		_nonPawnMaterialValue -= nonPawnMaterial;
	}
	
	inline void  GameState::MaterialPromotePiece( const simdScore material, const simdScore protmotedMaterial , const simdScore nonPawnPromotedMaterial )
	{
		_materialValue += protmotedMaterial - material;
		_nonPawnMaterialValue -= nonPawnPromotedMaterial;
	}

	class Position
	{
	
	public:
		
		
	private:
		
	};
}


#endif

