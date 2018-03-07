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

#ifndef POSITION_H_
#define POSITION_H_

#include <vector>
#include <array>
#include "State.h"
#include "BitMap.h"
#include "BitBoardIndex.h"

namespace libChess
{
	class Position
	{
	public:
		/*****************************************************************
		*	constructors
		******************************************************************/
		Position();
		Position(const Position& other);
		
		/*****************************************************************
		*	Operators
		******************************************************************/
		Position& operator=(const Position& other);
		
		/*****************************************************************
		*	Getters
		******************************************************************/
		const GameState& getActualStateConst(void)const;
		const GameState& getState(unsigned int n)const;
		unsigned int getStateSize() const;
		
		const baseTypes::BitMap& getOccupationBitmap() const;
		const baseTypes::BitMap& getBitmap(const baseTypes::bitboardIndex in) const;
		baseTypes::tSquare getSquareOfThePiece(const baseTypes::bitboardIndex piece) const;
		const baseTypes::BitMap& getOurBitmap( const baseTypes::bitboardIndex piece )const;
		const baseTypes::BitMap& getTheirBitmap( const baseTypes::bitboardIndex piece )const;
		unsigned int getPieceCount(const baseTypes::bitboardIndex in) const;
		baseTypes::bitboardIndex getPieceAt(const baseTypes::tSquare sq) const;
		
		baseTypes::bitboardIndex getMyPiece(const baseTypes::bitboardIndex in) const;
		baseTypes::bitboardIndex getEnemyPiece(const baseTypes::bitboardIndex in) const;
		
		const std::string getFen(void) const;
		const std::string getSymmetricFen(void) const;
		
		/*****************************************************************
		*	Methods
		******************************************************************/
		bool isWhiteTurn() const;
		bool isBlackTurn() const;
		const std::string display(void) const;
		bool setupFromFen(const std::string& fenStr= "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		
		const baseTypes::BitMap getAttackersTo(const baseTypes::tSquare to) const;
		const baseTypes::BitMap getAttackersTo(const baseTypes::tSquare to, const baseTypes::BitMap& occupancy ) const;
		
		void doNullMove( void );
		void undoNullMove( void );
		void doMove( const Move &m );
		void undoMove( void );
		
		
	
	private:
	
		/*****************************************************************
		*	Members
		******************************************************************/
		std::vector<GameState> _stateList;
		// todo valutate the use of a iterator
		GameState* _actualState;
		std::array< baseTypes::bitboardIndex, baseTypes::squareNumber > _squares; // board square rapresentation to speed up, it contain pieces indexed by square
		std::array< baseTypes::BitMap, baseTypes::bitboardNumber > _bitBoard;     // bitboards indexed by baseTypes::bitboardIndex enum
		// todo valutate the use of a iterator
		baseTypes::BitMap *_us,*_them;	/*!< pointer to our & their pieces bitboard*/
		
	private:
	
		/*****************************************************************
		*	methods
		******************************************************************/
		GameState& _getActualState( void );
		GameState& _pushState( void );
		void _popState( void );
		
		void _clearStateList( void );
		void _clear(void);
		
		void _setUsThem( void );
		void _swapUsThem();
		
		void _addPiece( const baseTypes::bitboardIndex piece, const baseTypes::tSquare s );
		void _removePiece(const baseTypes::bitboardIndex piece,const baseTypes::tSquare s);
		void _movePiece(const baseTypes::bitboardIndex piece, const baseTypes::tSquare from, const baseTypes::tSquare to);
		
		HashKey _calcKey(void) const;
		HashKey _calcPawnKey(void) const;
		HashKey _calcMaterialKey(void) const;
		void _calcCheckingSquares(void);
		const baseTypes::BitMap _calcPin(const baseTypes::tSquare kingSquare,const baseTypes::eTurn turn) const;
		
		bool _setupCastleRight(const baseTypes::tSquare rsq);
	
		
	};
	
	inline const GameState& Position::getActualStateConst(void)const
	{
		return *_actualState;
	}
	
	inline GameState& Position::_getActualState(void)
	{
		return *_actualState;
	}
	
	inline const baseTypes::BitMap& Position::getOccupationBitmap() const
	{
		return _bitBoard[ baseTypes::occupiedSquares ];
	}
	
	inline const baseTypes::BitMap& Position::getBitmap( const baseTypes::bitboardIndex in ) const
	{
		return _bitBoard[in];
	}
	
	inline unsigned int Position::getPieceCount( const baseTypes::bitboardIndex in ) const
	{
		return getBitmap( in ).bitCnt();
	}

	inline baseTypes::bitboardIndex Position::getPieceAt(const baseTypes::tSquare sq) const
	{
		return _squares[sq];
	}
	
	inline baseTypes::tSquare Position::getSquareOfThePiece(const baseTypes::bitboardIndex piece) const
	{
		return getBitmap(piece).firstOne();
	}
	inline const baseTypes::BitMap& Position::getOurBitmap( const baseTypes::bitboardIndex piece )const
	{
		return _us[ piece ];
	}
	inline const baseTypes::BitMap& Position::getTheirBitmap( const baseTypes::bitboardIndex piece )const
	{
		return _them[ piece ];
	}
	
	inline const baseTypes::BitMap Position::getAttackersTo(const baseTypes::tSquare to) const
	{
		return getAttackersTo(to, _bitBoard[ baseTypes::occupiedSquares] );
	}
	
	inline bool Position::isWhiteTurn(void) const
	{
		return getActualStateConst().getTurn() == baseTypes::whiteTurn;
	}
	
	inline bool Position::isBlackTurn(void) const
	{
		return getActualStateConst().getTurn() == baseTypes::blackTurn;
	}
	
	inline baseTypes::bitboardIndex Position::getMyPiece(const baseTypes::bitboardIndex in) const
	{
		return in + getActualStateConst().getTurn();
	}
	inline baseTypes::bitboardIndex Position::getEnemyPiece(const baseTypes::bitboardIndex in) const
	{
		return in + baseTypes::separationBitmap - getActualStateConst().getTurn();
	}
}


#endif

