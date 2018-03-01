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

#ifndef STATE_H_
#define STATE_H_

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
		
	public:
		
		/*****************************************************************
		*	constructors
		******************************************************************/
		GameState();
		
		
		/*****************************************************************
		*	getters
		******************************************************************/
		const HashKey& getKey() const;
		const HashKey& getPawnKey() const;
		const HashKey& getMaterialKey() const;
		
		const simdScore& getNonPawnMaterialValue() const;
		const simdScore& getMaterialValue() const;
		
		baseTypes::eTurn getTurn() const;
		baseTypes::eCastle getCastleRights() const;
		baseTypes::tSquare getEpSquare() const;
		
		std::string getCastleRightsString() const;
		std::string getEpSquareString() const;
		
		unsigned int getFiftyMoveCnt() const;
		unsigned int getPliesFromNullCnt() const;
		unsigned int getPliesCnt() const;
		unsigned int getFullMoveCounter() const;
		
		baseTypes::bitboardIndex getCapturedPiece() const;
		const baseTypes::BitMap& getCheckingSquare( const baseTypes::bitboardIndex idx ) const;
		
		const baseTypes::BitMap& getHiddenCheckers() const;
		const baseTypes::BitMap& getPinned() const;
		const baseTypes::BitMap& getCheckers() const;
		
		const Move& getCurrentMove() const;
		
	protected:
		/*****************************************************************
		*	setters methods, doesn't update keys
		******************************************************************/
		void setKeys( const HashKey& key, const HashKey& pawnKey, const HashKey& materialKey );
		
		void setMaterialValues( const simdScore materialValue, const simdScore nonPawnMaterialValue );
		
		void setTurn( const baseTypes::eTurn turn);
		
		void setCastleRights( const baseTypes::eCastle cr );
		void setCastleRight( const baseTypes::eCastle cr );
		void resetAllCastleRights();
		
		void setFiftyMoveCnt( const unsigned int fmc );
		void setPliesCnt( const unsigned int cnt );
		
		void setCurrentMove( const Move& m );
		void setEpSquare( const baseTypes::tSquare sq );
		
		void setCapturedPiece( const baseTypes::bitboardIndex idx );
		void resetCapturedPiece();
		
		void setCheckingSquare( const baseTypes::bitboardIndex idx, const baseTypes::BitMap& b );
		void setHiddenChechers( const baseTypes::BitMap& b);
		void setPinned( const baseTypes::BitMap& b);
		void setCheckers( const baseTypes::BitMap& b );
			
		/*****************************************************************
		*	update method, if necessary update keys
		******************************************************************/
		
		void changeTurn();
		
		void incrementCounters();
		void incrementCountersNullMove();
		void resetCountersNullMove();
		void resetFiftyMoveCnt();
		
		void clearEpSquare();
		void addEpSquare( const baseTypes::tSquare sq );
		
		void clearCastleRight( const int cr );
		
		void keyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq);
		void keyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq);
		void keyPromotePiece(const baseTypes::bitboardIndex piece, const baseTypes::bitboardIndex promotedPiece, const baseTypes::tSquare sq);
		
		void pawnKeyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq);
		void pawnKeyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq);
		
		void materialKeyRemovePiece(const baseTypes::bitboardIndex p, unsigned int count);
		void materialKeyPromovePiece(const baseTypes::bitboardIndex piece, const unsigned int count, const baseTypes::bitboardIndex promotedPiece, const unsigned int promotedCount);
		
		void materialMovePiece( const simdScore from, const simdScore to );
		void materialCapturePiece( const simdScore material, const simdScore nonPawnMaterial );
		void materialPromotePiece( const simdScore material, const simdScore promotedMaterial , const simdScore nonPawnPromotedMaterial );
		
		/*****************************************************************
		*	other methods
		******************************************************************/
		bool hasCastleRight( const baseTypes::eCastle cr) const;
		bool hasEpSquareSet(void)const;
		
		
	private:
		HashKey 
			_key,		/*!<  hashkey identifying the position*/
			_pawnKey,	/*!<  hashkey identifying the pawn formation*/
			_materialKey;/*!<  hashkey identifying the material signature*/
			
		simdScore _nonPawnMaterialValue; 	/*!< four score used for white/black opening/endgame non pawn material sum*/
		simdScore _materialValue;			/*!< material value of the position*/
		
		/* todo spostare fuori dal gamestate? */
		baseTypes::eTurn _turn;	/*!< who is the active player*/
		baseTypes::eCastle _castleRights; /*!<  actual castle rights*/
		baseTypes::tSquare _epSquare;	/*!<  en passant square*/
		
		unsigned int 
		/* todo unificare _fiftyMoveCnt e _pliesFromNull?? */
			_fiftyMoveCnt,	/*!<  50 move count used for draw rule*/
			_pliesFromNull,	/*!<  plies from null move*/
		/* todo spostare fuori dal gamestate? */
			_ply;			/*!<  ply from the start*/
			
		baseTypes::bitboardIndex _capturedPiece; /*!<  index of the captured piece for unmakeMove*/
		
		baseTypes::BitMap _checkingSquares[baseTypes::bitboardNumber]; /*!< squares of the board from where a king can be checked*/
		baseTypes::BitMap _hiddenCheckers;	/*!< pieces who can make a discover check moving*/
		baseTypes::BitMap _pinned;	/*!< pinned pieces*/
		baseTypes::BitMap _checkers;	/*!< checking pieces*/
		Move _currentMove;
		
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
	
	inline const simdScore& GameState::getNonPawnMaterialValue() const { return _nonPawnMaterialValue; }
	inline const simdScore& GameState::getMaterialValue()    const { return _materialValue; }
	
	inline baseTypes::eTurn GameState::getTurn()             const {return _turn; }
	inline baseTypes::eCastle GameState::getCastleRights()   const {return _castleRights; }
	inline baseTypes::tSquare GameState::getEpSquare()       const {return _epSquare; }
	
	inline unsigned int GameState::getFiftyMoveCnt()         const { return _fiftyMoveCnt; }
	inline unsigned int GameState::getPliesFromNullCnt()     const { return _pliesFromNull; }
	inline unsigned int GameState::getPliesCnt()             const { return _ply; }
	
	inline baseTypes::bitboardIndex GameState::getCapturedPiece()       const { return _capturedPiece; }
	inline const baseTypes::BitMap& GameState::getCheckingSquare( const baseTypes::bitboardIndex idx ) const { return _checkingSquares[idx]; }
	
	inline const baseTypes::BitMap& GameState::getHiddenCheckers()      const { return _hiddenCheckers; }
	inline const baseTypes::BitMap& GameState::getPinned()   const { return _pinned; }
	inline const baseTypes::BitMap& GameState::getCheckers() const { return _checkers; }
	
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
	
	inline void GameState::setTurn( const baseTypes::eTurn turn)
	{
		_turn = turn;
	}
	
	inline void GameState::setCastleRights( const baseTypes::eCastle cr)
	{
		_castleRights = cr;
	}
	
	inline void GameState::setCastleRight( const baseTypes::eCastle cr)
	{
		_castleRights = (baseTypes::eCastle)(_castleRights | cr);
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
		_turn = (baseTypes::eTurn)( baseTypes::blackTurn - _turn );
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
	inline void GameState::resetCountersNullMove(void)
	{
		_pliesFromNull = 0;
	}
	
	inline void GameState::resetFiftyMoveCnt()
	{
		_fiftyMoveCnt = 0;
	}
	
	inline void GameState::clearEpSquare()
	{
		if( _epSquare != baseTypes::squareNone)
		{
			assert( _epSquare < baseTypes::squareNumber );
			_key.removeEp(_epSquare);
			_epSquare = baseTypes::squareNone;
		}
	}
	
	inline void GameState::setEpSquare( const baseTypes::tSquare sq)
	{
		assert( _epSquare == baseTypes::squareNone);
		assert( sq < baseTypes::squareNumber );
		_epSquare = sq;

	}
	
	inline void GameState::addEpSquare( const baseTypes::tSquare sq)
	{
		assert( _epSquare == baseTypes::squareNone);
		assert( sq < baseTypes::squareNumber );
		_epSquare = sq;
		_key.addEp(_epSquare);
	
	}
	
	
	inline void GameState::setCapturedPiece( const baseTypes::bitboardIndex idx )
	{
		assert( idx < bitboardNumber );
		_capturedPiece = idx;
	}
	inline void GameState::resetCapturedPiece()
	{
		_capturedPiece =baseTypes::empty;
	}
	
	inline void GameState::clearCastleRight( const int cr )
	{
		const baseTypes::eCastle filteredCR = baseTypes::eCastle(_castleRights & cr);
		// Update castle rights if needed
		if ( filteredCR )
		{
			assert( ( filteredCR ) < 16 );
			_key.changeCastlingRight( filteredCR );
			_castleRights = (baseTypes::eCastle)( _castleRights & (~filteredCR) );
		}
	}
	
	inline void GameState::resetAllCastleRights()
	{
		_castleRights = (baseTypes::eCastle)0;
	}
	
	inline void GameState::setPinned( const baseTypes::BitMap& b)
	{
		_pinned = b;
	}

	inline void GameState::setHiddenChechers( const baseTypes::BitMap& b)
	{
		_hiddenCheckers = b;
	}
	
	inline void GameState::setCheckers( const baseTypes::BitMap& b )
	{
		_checkers = b;
	}
	
	inline void GameState::setCheckingSquare( const baseTypes::bitboardIndex idx, const baseTypes::BitMap& b )
	{
		assert( idx < bitboardNumber );
		_checkingSquares[idx] = b;
	}
	
	inline void GameState::keyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq)
	{
		_key.movePiece( p, fromSq, toSq );
	}
	
	inline void GameState::keyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq)
	{
		_key.removePiece( p, sq );
	}
	
	inline void GameState::keyPromotePiece(const baseTypes::bitboardIndex piece, const baseTypes::bitboardIndex promotedPiece, const baseTypes::tSquare sq)
	{
		_key.removePiece( piece, sq).addPiece( promotedPiece, sq);
	}
	
	inline void GameState::pawnKeyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq)
	{
		_pawnKey.movePiece( p, fromSq, toSq );
	}
	
	inline void GameState::pawnKeyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq)
	{
		_pawnKey.removePiece( p, sq );
	}
	
	inline void GameState::materialKeyRemovePiece(const baseTypes::bitboardIndex p, unsigned int count)
	{
		_materialKey.removePiece( p, (baseTypes::tSquare)count );
	}
	
	inline void GameState::materialKeyPromovePiece(const baseTypes::bitboardIndex piece, const unsigned int count, const baseTypes::bitboardIndex promotedPiece, const unsigned int promotedCount)
	{
		_materialKey.removePiece( piece, (baseTypes::tSquare)count ).addPiece( promotedPiece, (baseTypes::tSquare)promotedCount );
	}
	
	inline void  GameState::materialMovePiece( const simdScore from, const simdScore to )
	{
		_materialValue += to - from;
	}
	
	inline void  GameState::materialCapturePiece( const simdScore material, const simdScore nonPawnMaterial )
	{
		_materialValue -= material;
		_nonPawnMaterialValue -= nonPawnMaterial;
	}
	
	inline void  GameState::materialPromotePiece( const simdScore material, const simdScore promotedMaterial, const simdScore nonPawnPromotedMaterial )
	{
		_materialValue += promotedMaterial - material;
		_nonPawnMaterialValue += nonPawnPromotedMaterial;
	}
	
	inline unsigned int GameState::getFullMoveCounter(void) const
	{
		return 1 + (getPliesCnt() - int( getTurn() == baseTypes::blackTurn ) ) / 2;
	}
	
	inline std::string GameState::getEpSquareString(void) const
	{
		std::string s;
		
		if( hasEpSquareSet() )
		{
			s = to_string( getEpSquare() );
		}
		else
		{
			s = "-";
		}
		return s;
	}
	
	inline std::string GameState::getCastleRightsString(void) const
	{
		// TODO print chess960 CR
		std::string s;
		// castling rights
		bool hasSomeCastleRight = false;
		if( hasCastleRight( baseTypes::wCastleOO ) )
		{
			s += "K";
			hasSomeCastleRight = true;
		}
		if( hasCastleRight( baseTypes::wCastleOOO) )
		{
			s += "Q";
			hasSomeCastleRight = true;
		}
		if( hasCastleRight( baseTypes::bCastleOO) )
		{
			s += "k";
			hasSomeCastleRight = true;
		}
		if( hasCastleRight( baseTypes::bCastleOOO) )
		{
			s += "q";
			hasSomeCastleRight = true;
		}
		
		if( false == hasSomeCastleRight )
		{
			s += "-";
		}
		
		return s;
	}
	
	inline bool GameState::hasCastleRight( const baseTypes::eCastle cr ) const
	{
		return _castleRights & cr;
	}
	
	inline bool GameState::hasEpSquareSet() const
	{
		return _epSquare != baseTypes::squareNone;
	}
}

#endif