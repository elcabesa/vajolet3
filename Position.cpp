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

#include <utility>
#include "Position.h"

namespace libChess
{
	Position::Position()
	{
		_clearStateList();
		
		_getActualState().setTurn( whiteTurn );
		
		_setUsThem();
	}
	
	Position::Position(const Position& other):_stateList(other._stateList), _squares(other._squares),_bitBoard(other._bitBoard)
	{
		_actualState = &_stateList.back();
		
		_setUsThem();
		
	}
	
	Position& Position::operator=(const Position& other)
	{
		if (this == &other)
			return *this;

		_stateList = other._stateList;
		_actualState = &_stateList.back();
		
		
		_squares = other._squares;
		_bitBoard = other._bitBoard;

		_setUsThem();

		return *this;
	}
	
	
	inline void Position::_clearStateList(void)
	{
		_stateList.clear();
		_stateList.emplace_back(GameState());
		_actualState = &_stateList.back();
		
	}
	
	inline GameState& Position::_pushState(void)
	{
		_stateList.emplace_back(getActualStateConst());
		_actualState = &_stateList.back();
		return _getActualState();
	}
	
	inline void Position::_popState(void)
	{
		_stateList.pop_back();
		_actualState = &_stateList.back();
	}
	
	const GameState& Position::getState(unsigned int n)const
	{
		return _stateList[n];	
	}
	
	unsigned int Position::getStateSize() const
	{
		return _stateList.size();
	}
	
	
	inline void Position::_setUsThem(void)
	{
		eTurn turn = getActualStateConst().getTurn();
		
		_Us = &_bitBoard[ turn ];
		_Them = &_bitBoard[ getSwitchedTurn(turn) ];
	}
	
	inline void Position::_swapUsThem()
	{
		std::swap( _Us , _Them );
	}
	
	inline void Position::_addPiece( const bitboardIndex piece, const tSquare s )
	{
		//assert(s<squareNumber);
		//assert(piece<lastBitboard);
		
		const bitboardIndex MyPieces = getMyPiecesfromPiece(piece);
		// todo check if it's fast enough
		const BitMap b = BitMap::getBitmapFromSquare(s);

		//assert(squares[s]==empty);

		_squares[ s ] = piece;
		_bitBoard[ piece ] += b;
		_bitBoard[ occupiedSquares ] += b;
		_bitBoard[ MyPieces ] += b;
	}
	
	inline void Position::_removePiece(const bitboardIndex piece,const tSquare s)
	{

		//assert(!isKing(piece));
		//assert(s<squareNumber);
		//assert(piece<lastBitboard);
		//assert(squares[s]!=empty);

		// WARNING: This is not a reversible operation. If we remove a piece in
		// do_move() and then replace it in undo_move() we will put it at the end of
		// the list and not in its original place, it means index[] and pieceList[]
		// are not guaranteed to be invariant to a do_move() + undo_move() sequence.
		const bitboardIndex MyPieces = getMyPiecesfromPiece(piece);
		
		const BitMap b = BitMap::getBitmapFromSquare(s);

		_squares[ s ] = empty;
		_bitBoard[ occupiedSquares ] ^= b;
		_bitBoard[ piece ] ^= b;
		_bitBoard[ MyPieces ] ^= b;

	}
	
	inline void Position::_movePiece(const bitboardIndex piece, const tSquare from, const tSquare to)
	{
		//assert(from<squareNumber);
		//assert(to<squareNumber);
		//assert(piece<lastBitboard);
		
		//assert(squares[from]!=empty);
		//assert(squares[to]==empty);
		const bitboardIndex MyPieces = getMyPiecesfromPiece(piece);
		
		const BitMap fromTo = BitMap::getBitmapFromSquare( from ) ^ to;
		
		_squares[from] = empty;
		_squares[to] = piece;
		
		_bitBoard[occupiedSquares] ^= fromTo;
		_bitBoard[piece] ^= fromTo;
		_bitBoard[MyPieces] ^= fromTo;
		


	}
	
	
	
}