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
		
		const baseTypes::BitMap& getOccupationBitMap() const;
		const baseTypes::BitMap& getBitmap(const baseTypes::bitboardIndex in) const;
		baseTypes::tSquare getSquareOfThePiece(const baseTypes::bitboardIndex piece) const;
		baseTypes::tSquare getSquareOfWhiteKing() const;
		baseTypes::tSquare getSquareOfBlackKing() const;
		baseTypes::tSquare getSquareOfMyKing() const;
		baseTypes::tSquare getSquareOfEnemyKing() const;
		
		const baseTypes::BitMap& getOurBitMap( const baseTypes::bitboardIndex piece = baseTypes::Pieces )const;
		const baseTypes::BitMap& getTheirBitMap( const baseTypes::bitboardIndex piece = baseTypes::Pieces )const;
		const baseTypes::BitMap getOurQRSlidingBitMap()const;
		const baseTypes::BitMap getTheirQRSlidingBitMap()const;
		const baseTypes::BitMap getOurQBSlidingBitMap()const;
		const baseTypes::BitMap getTheirQBSlidingBitMap()const;
		
		unsigned int getPieceCount(const baseTypes::bitboardIndex in) const;
		baseTypes::bitboardIndex getPieceAt(const baseTypes::tSquare sq) const;
		
		baseTypes::bitboardIndex getMyPiece(const baseTypes::bitboardIndex in) const;
		baseTypes::bitboardIndex getEnemyPiece(const baseTypes::bitboardIndex in) const;
		
		const std::string getFen(void) const;
		const std::string getSymmetricFen(void) const;
		const baseTypes::BitMap& getKingCastlePath( const baseTypes::tColor color, const bool kingSide ) const;
		const baseTypes::BitMap& getCastleOccupancyPath( const baseTypes::tColor color, const bool kingSide ) const;
		baseTypes::tSquare getCastleRookInvolved( const baseTypes::tColor color, const bool kingSide ) const;
		
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
		void doMove( const Move& m );
		void undoMove( void );
		
		bool moveGivesCheck( const Move& m ) const;
		bool moveGivesDoubleCheck( const Move& m ) const;
		bool moveGivesSafeDoubleCheck( const Move& m ) const;
		
		Score getMvvLvaScore( const Move& m ) const;
		
		bool isInCheck( void ) const;
		
		
	
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
		std::array< baseTypes::eCastle, baseTypes::squareNumber > _castleRightsMask;	// cr mask used to speed up do move
		
		// todo _castleKingPath & _castleRookPath possomno essere uniti in una sola bitmap in or
		std::array< baseTypes::BitMap, 4 > _castleKingPath;	// path to be traversed by the king when castling
		std::array< baseTypes::BitMap, 4 > _castleOccupancyPath;	// path that need to be free to be able to castle
		std::array< baseTypes::tSquare, 4 > _castleRookInvolved;	// rook involved in the castling
		
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
		const baseTypes::BitMap _calcPin( const baseTypes::tSquare kingSquare, const baseTypes::BitMap& bishopLikeBitMap, const baseTypes::BitMap& rookLikeBitMap ) const;
		
		bool _setupCastleRight(const baseTypes::tSquare rsq);
		bool _tryAddCastleRight( const baseTypes::eCastle cr, const baseTypes::tSquare ksq, const baseTypes::tSquare rsq );
		
		bool _setupCastlePath(const baseTypes::tColor color, const bool kingSide, const baseTypes::tSquare KingSquare, const baseTypes::tSquare RookSquare);
		static unsigned int _calcCRPIndex( const baseTypes::tColor color, const bool kingSide );
		
		void _clearCastleRightsMask(void);
		void _clearCastleRightsPaths(void);
		void _clearCastleRookInvolved(void);
		
	
		
	};
	
	inline const GameState& Position::getActualStateConst(void)const
	{
		return *_actualState;
	}
	
	inline GameState& Position::_getActualState(void)
	{
		return *_actualState;
	}
	
	inline const baseTypes::BitMap& Position::getOccupationBitMap() const
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
	
	inline baseTypes::tSquare Position::getSquareOfWhiteKing() const
	{
		// todo provare a fare un codice migliore, probabilmente si puo aggiungere la posizione dei re nella classe
		return getBitmap(baseTypes::whiteKing).firstOne();
	}
	inline baseTypes::tSquare Position::getSquareOfBlackKing() const
	{
		// todo provare a fare un codice migliore, probabilmente si puo aggiungere la posizione dei re nella classe
		return getBitmap(baseTypes::blackKing).firstOne();
	}
	inline baseTypes::tSquare Position::getSquareOfMyKing() const
	{
		// todo provare a fare un codice migliore, probabilmente si puo aggiungere la posizione dei re nella classe
		return getBitmap( getMyPiece( baseTypes::King ) ).firstOne();
	}
	inline baseTypes::tSquare Position::getSquareOfEnemyKing() const
	{
		// todo provare a fare un codice migliore, probabilmente si puo aggiungere la posizione dei re nella classe
		return getBitmap( getEnemyPiece( baseTypes::King ) ).firstOne();
	}
	
	inline const baseTypes::BitMap& Position::getOurBitMap( const baseTypes::bitboardIndex piece )const
	{
		return _us[ piece ];
	}
	inline const baseTypes::BitMap& Position::getTheirBitMap( const baseTypes::bitboardIndex piece )const
	{
		return _them[ piece ];
	}
	
	inline const baseTypes::BitMap Position::getOurQRSlidingBitMap()const
	{
		return _us[ baseTypes::Queens ] + _us[ baseTypes::Rooks ];
	}
	inline const baseTypes::BitMap Position::getTheirQRSlidingBitMap()const
	{
		return _them[ baseTypes::Queens ] + _them[ baseTypes::Rooks ];
	}
	inline const baseTypes::BitMap Position::getOurQBSlidingBitMap()const
	{
		return _us[ baseTypes::Queens ] + _us[ baseTypes::Bishops ];
	}
	inline const baseTypes::BitMap Position::getTheirQBSlidingBitMap()const
	{
		return _them[ baseTypes::Queens ] + _them[ baseTypes::Bishops ];
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
	
	// todo move this function as public of state to speedup move generation
	inline baseTypes::bitboardIndex Position::getMyPiece(const baseTypes::bitboardIndex in) const
	{
		return in + getActualStateConst().getTurn();
	}
	inline baseTypes::bitboardIndex Position::getEnemyPiece(const baseTypes::bitboardIndex in) const
	{
		return in + baseTypes::separationBitmap - getActualStateConst().getTurn();
	}
	
	inline unsigned int Position::_calcCRPIndex( const baseTypes::tColor color, const bool kingSide )
	{
		return ( color * 2 ) + kingSide;
	}
	
	inline const baseTypes::BitMap& Position::getKingCastlePath( const baseTypes::tColor color, const bool kingSide ) const
	{
		return _castleKingPath[ _calcCRPIndex( color, kingSide ) ];
	}
	
	inline const baseTypes::BitMap& Position::getCastleOccupancyPath( const baseTypes::tColor color, const bool kingSide ) const
	{
		return _castleOccupancyPath[ _calcCRPIndex( color, kingSide ) ];
	}
	
	inline baseTypes::tSquare Position::getCastleRookInvolved( const baseTypes::tColor color, const bool kingSide ) const
	{
		return _castleRookInvolved[ _calcCRPIndex( color, kingSide ) ];
	}
	
	inline Score Position::getMvvLvaScore( const Move& m ) const
	{	
		const Score MVVValue[] = { 0, 3000, 900, 500, 350, 300, 100, 0, 0, 3000, 900, 500, 350, 300, 100, 0 } ;
		const Score LVAValue[] = { 0, 30, 9, 5, 3, 2, 1, 0, 0, 30, 9, 5, 3, 2, 1, 0 } ;
		assert( isValidPiece( getPieceAt( m.getFrom() ) ) );
		assert( isValidPiece( getPieceAt( m.getTo() ) ) || m.isEnPassantMove() );
		
		Score s = MVVValue[ getPieceAt( m.getTo() ) ] - LVAValue[ getPieceAt( m.getFrom() ) ];
				
		/*if ( m.isPromotionMove() )
		{
			s += (pieceValue[ baseTypes::whiteQueens +m.bit.promotion ] - pieceValue[whitePawns])[0];
		}
		else */if( m.isEnPassantMove() )
		{
			//todo questo può essere eliminato mettendo MVVValue[empty ] = 100;
			s += MVVValue[ baseTypes::whitePawns ];
		}
		
		return s;
	}
	
	inline bool Position::isInCheck( void ) const
	{
		return !getActualStateConst().getCheckers().isEmpty();
	}
}


#endif

