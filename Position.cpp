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

#include <utility>
#include <sstream>
#include "Position.h"
#include "BitMapMoveGenerator.h"
#include "MoveGenerator.h"

namespace libChess
{
	Position::Position()
	{
		_clearStateList();
		
		_getActualState().setTurn( baseTypes::whiteTurn );
		
		_setUsThem();
	}
	
	Position::Position(const Position& other):_stateList(other._stateList), _squares(other._squares),_bitBoard(other._bitBoard), _castleRightsMask(other._castleRightsMask)
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
		
		_castleRightsMask = other._castleRightsMask;

		_setUsThem();

		return *this;
	}
	
	
	inline void Position::_clearStateList(void)
	{
		_stateList.clear();
		_stateList.emplace_back(GameState());
		_actualState = &_stateList.back();
		
	}
	
	
	inline void Position::_clear()
	{
		for (auto& piece : _squares)
		{
			piece = baseTypes::empty;
		}
		for (auto& b : _bitBoard)
		{
			b.clear();
		}
		_clearStateList();
	}
	
	inline GameState& Position::_pushState(void)
	{
		_stateList.emplace_back( getActualStateConst() );
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
		baseTypes::eTurn turn = getActualStateConst().getTurn();
		
		_us = &_bitBoard[ turn ];
		_them = &_bitBoard[ getSwitchedTurn(turn) ];
	}
	
	inline void Position::_swapUsThem()
	{
		std::swap( _us , _them );
	}
	
	inline void Position::_addPiece( const baseTypes::bitboardIndex piece, const baseTypes::tSquare s )
	{
		assert( s < baseTypes::squareNumber );
		assert( piece < baseTypes::bitboardNumber );
		
		const baseTypes::bitboardIndex MyPieces = getMyPiecesFromPiece(piece);
		// todo check if it's fast enough
		const baseTypes::BitMap b = baseTypes::BitMap::getBitmapFromSquare(s);

		assert( _squares[ s ] ==  baseTypes::empty);
		assert( _bitBoard[ piece ].isSquareSet( s ) ==  false );
		assert( _bitBoard[ baseTypes::occupiedSquares ].isSquareSet( s ) ==  false );
		assert( _bitBoard[ MyPieces ].isSquareSet( s ) ==  false );

		_squares[ s ] = piece;
		_bitBoard[ piece ] += b;
		_bitBoard[ baseTypes::occupiedSquares ] += b;
		_bitBoard[ MyPieces ] += b;
	}
	
	inline void Position::_removePiece(const baseTypes::bitboardIndex piece,const baseTypes::tSquare s)
	{

		assert( !baseTypes::isKing( piece ) );
		assert( s < baseTypes::squareNumber);
		assert( piece < baseTypes::bitboardNumber );
		assert( _squares[ s ] != baseTypes::empty );

		// WARNING: This is not a reversible operation. If we remove a piece in
		// do_move() and then replace it in undo_move() we will put it at the end of
		// the list and not in its original place, it means index[] and pieceList[]
		// are not guaranteed to be invariant to a do_move() + undo_move() sequence.
		const baseTypes::bitboardIndex MyPieces = getMyPiecesFromPiece(piece);
		
		const baseTypes::BitMap b = baseTypes::BitMap::getBitmapFromSquare(s);

		_squares[ s ] = baseTypes::empty;
		_bitBoard[ baseTypes::occupiedSquares ] ^= b;
		_bitBoard[ piece ] ^= b;
		_bitBoard[ MyPieces ] ^= b;

	}
	
	inline void Position::_movePiece(const baseTypes::bitboardIndex piece, const baseTypes::tSquare from, const baseTypes::tSquare to)
	{
		assert( from < baseTypes::squareNumber );
		assert( to < baseTypes::squareNumber );
		assert( piece < baseTypes::bitboardNumber );
		
		assert( _squares[from] != baseTypes::empty );
		assert( _squares[to] == baseTypes::empty );
		
		const baseTypes::bitboardIndex MyPieces = getMyPiecesFromPiece(piece);
		
		const baseTypes::BitMap fromTo = baseTypes::BitMap::getBitmapFromSquare( from ) ^ to;
		
		_squares[from] = baseTypes::empty;
		_squares[to] = piece;
		
		_bitBoard[baseTypes::occupiedSquares] ^= fromTo;
		_bitBoard[piece] ^= fromTo;
		_bitBoard[MyPieces] ^= fromTo;
		


	}
	
	
	HashKey Position::_calcKey(void) const
	{
		HashKey hash;
		const GameState& st = getActualStateConst();

		for(auto t: baseTypes::tSquareRange())
		{
			if( _squares[t] != baseTypes::empty )
			{
				hash.addPiece( _squares[t], t );
			}
		}

		if( isBlackTurn() )
		{
			hash.changeSide();
		}
		
		hash.changeCastlingRight( st.getCastleRights() );

		baseTypes::tSquare epSq = st.getEpSquare();
		if( epSq != baseTypes::squareNone )
		{
			hash.addEp(epSq);
		}

		return hash;
	}
	

	HashKey Position::_calcPawnKey(void) const
	{
		HashKey hash(1);
		
		for(const auto t : getBitmap( baseTypes::whitePawns ) )
		{
			hash.addPiece( baseTypes::whitePawns, t );
		}
		
		for(const auto t : getBitmap( baseTypes::blackPawns ) )
		{
			hash.addPiece( baseTypes::blackPawns, t );
		}
		return hash;
	}


	HashKey Position::_calcMaterialKey(void) const
	{
		HashKey hash;
		for( const auto p: baseTypes::bitboardIndexRange())
		{
			if ( baseTypes::isValidPiece(p) )
			{
				for ( unsigned int cnt = 0; cnt < getPieceCount( p ); ++cnt )
				{
					hash.addPiece( p, (baseTypes::tSquare)cnt );
				}
			}
		}

		return hash;
	}	
	
	/*	\brief display the fen string of the position
	\author Marco Belli
	\version 1.0
	\date 15/02/2018
	*/
	const std::string Position::getFen(void) const
	{
		std::string s;
		
		const GameState& st = getActualStateConst();
		
		// write rank
		for( const auto rank: baseTypes::tRankNegativeRange() )
		{
			unsigned int emptyFiles = 0u;
			// for ech file
			for( const auto file: baseTypes::tFileRange() )
			{
				const baseTypes::tSquare sq = getSquareFromFileRank( file, rank );
				const baseTypes::bitboardIndex piece = getPieceAt( sq );
				
				// write piece...
				if( isValidPiece(piece) )
				{
					// ...prepending empty square number
					if( emptyFiles != 0 )
					{
						s += std::to_string( emptyFiles );
					}
					emptyFiles = 0u;
					
					s += getPieceName( piece );
				}
				else
				{
					++emptyFiles;
				}
			}
			// append empty squares after last piece on row
			if( emptyFiles != 0 )
			{
				s += std::to_string(emptyFiles);
			}
			// append '/' if needed
			if( rank != baseTypes::tRank::one )
			{
				s += "/";
			}
		}
		
		
		// turn
		s += " ";
		if( isBlackTurn() )
		{
			s += "b";
		}
		else
		{
			s += "w";
		}
		s += " ";
		
		// castling rights
		s += st.getCastleRightsString();
		s += " ";
		
		// epsquare
		s += st.getEpSquareString();
		
		s += " ";
		// half move clock
		s += std::to_string( st.getFiftyMoveCnt() );
		// full move clock
		s += " " + std::to_string( st.getFullMoveCounter() );
		
		return s;
	}
	
	
	/*	\brief display the fen string of the symmetrical position
	\author Marco Belli
	\version 1.0
	\date 15/02/2018
	*/
	const std::string Position::getSymmetricFen(void) const
	{
		std::string s;
		
		const GameState& st = getActualStateConst();
		GameState symmSt = st;
		
		// write rank
		for( const auto rank: baseTypes::tRankRange() )
		{
			unsigned int emptyFiles = 0u;
			// for ech file
			for( const auto file: baseTypes::tFileRange() ) 
			{
				const baseTypes::tSquare sq =getSquareFromFileRank( file, rank );
				const baseTypes::bitboardIndex piece = getPieceAt( sq );
				
				// write piece...
				if( isValidPiece(piece) )
				{
					// ...prepending empty square number
					if( emptyFiles != 0 )
					{
						s += std::to_string( emptyFiles );
					}
					emptyFiles = 0u;
					
					baseTypes::bitboardIndex symPiece = piece;
					if( baseTypes::isBlackPiece( symPiece ) )
					{
						symPiece -= baseTypes::separationBitmap;
					}
					else
					{
						symPiece += baseTypes::separationBitmap;
					}
					s += baseTypes::getPieceName( symPiece );
				}
				else
				{
					++emptyFiles;
				}
			}
			// append empty squares after last piece on row
			if(emptyFiles!=0)
			{
				s += std::to_string(emptyFiles);
			}
			// append '/' if needed
			if( rank != baseTypes::tRank::one )
			{
				s += "/";
			}
		}
		
		// turn
		s += " ";
		if( isBlackTurn() )
		{
			s += "w";
		}
		else
		{
			s += "b";
		}
		s += " ";
		
		// castling rights
		symmSt.resetAllCastleRights();
		if( st.hasCastleRight( baseTypes::wCastleOO ) ) symmSt.setCastleRight( baseTypes::bCastleOO );
		if( st.hasCastleRight( baseTypes::wCastleOOO ) ) symmSt.setCastleRight( baseTypes::bCastleOOO );
		if( st.hasCastleRight( baseTypes::bCastleOO ) ) symmSt.setCastleRight( baseTypes::wCastleOO );
		if( st.hasCastleRight( baseTypes::bCastleOOO ) ) symmSt.setCastleRight( baseTypes::wCastleOOO );
		s += symmSt.getCastleRightsString();
		
		s += " ";
		// epsquare
		const baseTypes::tSquare sq = st.getEpSquare();
		const baseTypes::tFile symFile = baseTypes::getFile(sq);
		baseTypes::tRank symRank = baseTypes::tRank::eight - getRank(sq);
		symmSt.setEpSquare(getSquareFromFileRank( symFile, symRank ));
		
		s += symmSt.getEpSquareString();
	
		s += " ";
		// half move clock
		s += std::to_string( st.getFiftyMoveCnt() );
		// full move clock
		s += " " + std::to_string( st.getFullMoveCounter()  );
		return s;
	}
	
	/*	\brief display a board for debug purpose
		\author Marco Belli
		\version 1.0
		\date 15/02/2018
	*/
	const std::string Position::display(void) const
	{
		const GameState& st = getActualStateConst();
		
		std::string s = getFen() + "\n";
		
		for( const auto rank: baseTypes::tRankNegativeRange() )
		{
			s += "  +---+---+---+---+---+---+---+---+\n";
			s += to_string(rank) +  " |";
			
			for( const auto file: baseTypes::tFileRange() )
			{
				const baseTypes::tSquare sq =getSquareFromFileRank( file, rank );
				const baseTypes::bitboardIndex piece = getPieceAt( sq );
				s += " " + baseTypes::getPieceName( piece ) + " |";
			}
			s += "\n";
			
		}
		s += "  +---+---+---+---+---+---+---+---+\n";
		s += " ";
		for(auto file: baseTypes::tFileRange())
		{
			s += "   " + to_string(file);
		}
		s += "\n";

		s += ( isWhiteTurn() ? "WHITE TO MOVE" : "BLACK TO MOVE");
		s += "\n";
		s += "50 move counter ";
		s += std::to_string( st.getFiftyMoveCnt() ) + "\n";
		s += "castleRights ";
		
		// castling rights
		s += st.getCastleRightsString();
		s += "\n";
		
		s += "epsquare ";
		s += st.getEpSquareString();
		s += "\n";
		
		s += "material ";
		s += st.getMaterialValue()[0]/10000.0;
		s += "\n";
		
		s += "white material  ";
		s += st.getNonPawnMaterialValue()[0]/10000.0;
		s += "\n";
		
		s += "black material  ";
		s += st.getNonPawnMaterialValue()[2]/10000.0;
		s += "\n";
		
		return s;

	}
	
	
	/*! \brief setup a position from a fen string
		\author Marco Belli
		\version 1.0
		\date 27/10/2013
	*/
	bool Position::setupFromFen(const std::string& fenStr)
	{
		char token;
		baseTypes::tSquare sq = baseTypes::A8;
		baseTypes::tFile file = baseTypes::A;
		
		std::istringstream ss(fenStr);
		ss >> std::noskipws;
		
		_clear();
		
		GameState &st = _getActualState();

		// parse piece list
		while( (ss >> token) && !std::isspace(token) )
		{
			
			if(token == '/')
			{
				
				sq -= baseTypes::tSquare(16);

				file = baseTypes::A;
				if( file < baseTypes::A || file > baseTypes::H || sq > baseTypes::H8 || sq < baseTypes::A1 )
				{
					return false;
				}
				
			}else if( isdigit(token) )
			{
				sq += baseTypes::tSquare( token - '0' ); // Advance the given number of files
				file += baseTypes::tFile( token - '0' );
			} 
			else
			{
				if( file < baseTypes::A || file > baseTypes::H || sq > baseTypes::H8 || sq < baseTypes::A1 )
				{
					return false;
				}
				
				baseTypes::bitboardIndex piece = baseTypes::getPieceFromUci(token);
				if( piece != baseTypes::empty )
				{
					_addPiece( piece, sq );
				}
				else
				{
					return false;
				}
				++sq;
			}
			
		}
		if( sq != baseTypes::A2 )
		{
			return false;
		}
		
		// turn
		ss >> token;
		if( token == 'w' )
		{
			st.setTurn(baseTypes::whiteTurn);
		}
		else if( token == 'b' )
		{
			st.setTurn(baseTypes::blackTurn);
		}
		else
		{
			return false;
		}
		_setUsThem();
		
		//space
		ss >> token;
		if( token !=' ')
		{
			return false;
		}
		
		// castle rights
		st.resetAllCastleRights();
		_clearCastleRightsMask();
		bool crEmpty = false;		

		while ( (ss >> token) && !isspace(token) )
		{
			switch(token)
			{
			case 'K':
			{
				baseTypes::tSquare rsq = baseTypes::H1;
				for( const auto sq : baseTypes::tSquareNegativeRange( getSquareOfThePiece(baseTypes::whiteKing), baseTypes::H1 ) )
				{
					if( getPieceAt( sq ) == baseTypes::whiteRooks )
					{
						rsq = sq;
						break;
					}
				}
				
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'Q':
			{
				baseTypes::tSquare rsq = baseTypes::A1;
				for( const auto sq : baseTypes::tSquareRange(  baseTypes::A1, getSquareOfThePiece(baseTypes::whiteKing) ) )
				{
					if( getPieceAt( sq ) == baseTypes::whiteRooks )
					{
						rsq = sq;
						break;
					}
				}
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'k':
			{
				baseTypes::tSquare rsq = baseTypes::H8;
				for( const auto sq : baseTypes::tSquareNegativeRange( getSquareOfThePiece(baseTypes::blackKing), baseTypes::H8 ) )
				{
					if( getPieceAt( sq ) == baseTypes::blackRooks )
					{
						rsq = sq;
						break;
					}
				}
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'q':
			{
				baseTypes::tSquare rsq = baseTypes::A8;
				for( const auto sq : baseTypes::tSquareRange(  baseTypes::A8, getSquareOfThePiece(baseTypes::blackKing) ) )
				{
					if( getPieceAt( sq ) == baseTypes::blackRooks )
					{
						rsq = sq;
						break;
					}
				}
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			{
				// white castling
				const baseTypes::tSquare rsq = baseTypes::getSquareFromFileRank( (baseTypes::tFile)((char)token -'A'), baseTypes::one );
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
	
			}
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			{
				// black castling
				const baseTypes::tSquare rsq = baseTypes::getSquareFromFileRank( (baseTypes::tFile)((char)token -'a'), baseTypes::eight );
				
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}	
			}
				
				break;
			case '-':
				if( st.getCastleRights() != 0 )
				{
					return false;
				}
				crEmpty = true;
				break;
			default:
				return false;
			}
		}
		
		ss >> token;
		
		// parse epsquare
		if( token == '-' )
		{
			st.setEpSquare( baseTypes::squareNone );
		}
		else
		{
			
			char col,row;
			if (
				( (ss >> col) && (col >= 'a' && col <= 'h') )
				&& ( (ss >> row) && ( row == '3' || row == '6' ) )
				)
			{
				st.setEpSquare( (baseTypes::tSquare) ( ( col - 'a' ) + 8 * ( row - '1' ) ) );
				
				// todo riguardare
				if ( ( getAttackersTo( st.getEpSquare() ) & getBitmap( getMyPiece( baseTypes::Pawns ) ) ).isEmpty() )
				{
					st.setEpSquare( baseTypes::squareNone );
				}
				
			}
			else
			{
				return false;
			}
			
		}
		
		
		ss >> token;
		if( token !=' ')
		{
			return false;
		}

		int fmc;
		ss >> std::skipws >> fmc;
		st.setFiftyMoveCnt(fmc);
		
		if( ss.eof() )
		{
			st.setPliesCnt( int( isBlackTurn() ) );
			st.resetFiftyMoveCnt();
		}
		else
		{
			int plies;
			ss >> plies;
			plies = std::max( 2 * ( plies - 1), 0) + int( isBlackTurn() );
			st.setPliesCnt( plies );
		}
		
		st.resetCountersNullMove();
		st.setCurrentMove( Move::NOMOVE );
		st.resetCapturedPiece();
		/*
		// todo readd those methods

		x.nonPawnMaterial = calcNonPawnMaterialValue();

		x.material=  calcMaterialValue();*/
		
		st.setKeys(_calcKey(), _calcPawnKey(), _calcMaterialKey() );


		
		
		_calcCheckingSquares();
	
		st.setDiscoveryChechers( _calcPin( getSquareOfThePiece( getEnemyPiece( baseTypes::King ) ), st.getTurn() ) );
		st.setPinned( _calcPin( getSquareOfThePiece( getMyPiece( baseTypes::King ) ), getSwitchedTurn( st.getTurn() ) ) );
		
		st.setCheckers( getAttackersTo( getSquareOfThePiece( getMyPiece( baseTypes::King ) ) ) & getBitmap( getEnemyPiece( baseTypes::blackPieces ) ) );

		


		/*
		// todo readd those methods
		checkPosConsistency(1);
		*/
		return true;
	}
	
	bool Position::_setupCastleRight(const baseTypes::tSquare rsq)
	{
		
		const baseTypes::tRank rookRank = getRank(rsq);
		
		if( rookRank != baseTypes::one && rookRank != baseTypes::eight )
		{
			return false;
		}
		
		const baseTypes::tSquare ksq = ( rookRank == baseTypes::one ? getSquareOfThePiece( baseTypes::whiteKing ) :getSquareOfThePiece( baseTypes::blackKing ) );
		const baseTypes::tRank kingRank = getRank(ksq);
		
		
		
		if( rookRank != kingRank )
		{
			return false;
		}
		
		if( !( baseTypes::isRook( getPieceAt( rsq ) ) ) )
		{
			return false;
		}
		
		baseTypes::eCastle cr;
		
		
		if ( kingRank == baseTypes::one ) 
		{
			cr = ( ksq < rsq ) ? baseTypes::wCastleOO : baseTypes::wCastleOOO;
		}
		else
		{
			cr = ( ksq < rsq ) ? baseTypes::bCastleOO : baseTypes::bCastleOOO;
		}
		
		if ( false == _tryAddCastleRight( cr, ksq, rsq ) )
		{
			return false;
		}
		return true;
	}
	
	bool Position::_tryAddCastleRight( const baseTypes::eCastle cr, const baseTypes::tSquare ksq, const baseTypes::tSquare rsq )
	{
		GameState &st = _getActualState();
		if( st.hasCastleRight( cr ) )
		{
			return false;
		}
		addCastleRightTo( _castleRightsMask[ ksq ], cr );
		addCastleRightTo( _castleRightsMask[ rsq ], cr );
		st.setCastleRight( cr );
		return true;
	}
	
	const baseTypes::BitMap Position::getAttackersTo(const baseTypes::tSquare to, const baseTypes::BitMap& occupancy ) const
	{
		assert( to < baseTypes::squareNumber);
		
		baseTypes::BitMap res = 
				// white pawns attack
				( BitMapMoveGenerator::getPawnAttack( to, baseTypes::black ) & getBitmap( baseTypes::whitePawns ) )
				// black pawns attack
				+ ( BitMapMoveGenerator::getPawnAttack( to, baseTypes::white ) & getBitmap( baseTypes::blackPawns ) )
				// knights attack
				+ ( BitMapMoveGenerator::getKnightMoves( to ) & ( getBitmap( baseTypes::whiteKnights ) + getBitmap( baseTypes::blackKnights ) ) )
				// king attack
				+ ( BitMapMoveGenerator::getKingMoves( to ) & ( getBitmap( baseTypes::whiteKing ) + getBitmap( baseTypes::blackKing ) ) );
		
		// bishop like movers
		baseTypes::BitMap mask = getBitmap( baseTypes::blackBishops ) + getBitmap( baseTypes::whiteBishops )+ getBitmap( baseTypes::blackQueens ) + getBitmap( baseTypes::whiteQueens );
		if( ( mask & BitMapMoveGenerator::getBishopPseudoMoves(to) ).isEmpty() == false )
		{
			res += ( BitMapMoveGenerator::getBishopMoves( to, occupancy ) & mask );
		}
		// rook like movers
		mask = getBitmap( baseTypes::blackRooks ) + getBitmap( baseTypes::whiteRooks )+ getBitmap( baseTypes::blackQueens ) + getBitmap( baseTypes::whiteQueens );
		if( ( mask & BitMapMoveGenerator::getRookPseudoMoves(to) ).isEmpty() == false )
		{
			res += ( BitMapMoveGenerator::getRookMoves( to, occupancy ) & mask );
		}
		
		return res;
	}
	
	/*! \brief calculate the checking squares given the king position
		\author Marco Belli
		\version 1.0
		\date 08/11/2013
	*/
	void Position::_calcCheckingSquares(void)
	{
		GameState &st = _getActualState();
		
		const baseTypes::bitboardIndex opponentKing = getEnemyPiece ( baseTypes::King );
		assert( opponentKing < baseTypes::bitboardNumber );


		const baseTypes::tSquare OppKingSquare = getSquareOfThePiece( opponentKing );

		const baseTypes::BitMap& occupancy = getOccupationBitmap();
		const baseTypes::tColor color = isBlackTurn() ?  baseTypes::white : baseTypes::black;

		st.setCheckingSquare( getMyPiece( baseTypes::King ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getMyPiece( baseTypes::Rooks ), BitMapMoveGenerator::getRookMoves( OppKingSquare, occupancy ) );
		st.setCheckingSquare( getMyPiece( baseTypes::Bishops ), BitMapMoveGenerator::getBishopMoves( OppKingSquare, occupancy ) );
		st.setCheckingSquare( getMyPiece( baseTypes::Queens ), BitMapMoveGenerator::getQueenMoves( OppKingSquare, occupancy ) );
		st.setCheckingSquare( getMyPiece( baseTypes::Knights ), BitMapMoveGenerator::getKnightMoves( OppKingSquare ) );
		st.setCheckingSquare( getMyPiece( baseTypes::Pawns ), BitMapMoveGenerator::getPawnAttack( OppKingSquare,color ) );

		st.setCheckingSquare( getEnemyPiece( baseTypes::King ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getEnemyPiece( baseTypes::Rooks ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getEnemyPiece( baseTypes::Bishops ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getEnemyPiece( baseTypes::Queens ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getEnemyPiece( baseTypes::Knights ), baseTypes::BitMap(0) );
		st.setCheckingSquare( getEnemyPiece( baseTypes::Pawns ), baseTypes::BitMap(0) );

	}
	
	
	const baseTypes::BitMap Position::_calcPin( const baseTypes::tSquare kingSquare, const baseTypes::eTurn turn ) const
	{
		assert( kingSquare < baseTypes::squareNumber );
		baseTypes::BitMap result(0);
		// calc pinners/pinned candidate
		baseTypes::BitMap pin = BitMapMoveGenerator::getBishopPseudoMoves( kingSquare ) & ( getBitmap( baseTypes::Bishops + turn ) + getBitmap( baseTypes::Queens + turn ) );
		pin += BitMapMoveGenerator::getRookPseudoMoves(kingSquare) & ( getBitmap( baseTypes::Rooks + turn ) + getBitmap( baseTypes::Queens + turn ) );

		for(  const auto pinSq : pin )
		{
			baseTypes::BitMap b = baseTypes::BitMap::getSquaresBetween( kingSquare, pinSq ) & getOccupationBitmap();
			if ( !b.moreThanOneBit() )
			{
				result += b & getBitmap( getMyPiece( baseTypes::Pieces ) );
			}
		}
		return result;

	}
	
	void Position::doNullMove( void )
	{
		GameState& st = _pushState();
		st.setCurrentMove( Move::NOMOVE );
		
		st.clearEpSquare();
		st.changeTurn();
		st.incrementCountersNullMove();
		st.resetCapturedPiece();
		
		_swapUsThem();
		
		_calcCheckingSquares();
	
		st.setDiscoveryChechers( _calcPin( getSquareOfThePiece( getEnemyPiece( baseTypes::King ) ), st.getTurn() ) );
		st.setPinned( _calcPin( getSquareOfThePiece( getMyPiece( baseTypes::King ) ), getSwitchedTurn( st.getTurn() ) ) );
		
		// checker doesn't change, don't update them
		//st.setCheckers( getAttackersTo( getSquareOfThePiece( getMyPiece( baseTypes::King ) ) ) & getBitmap( getEnemyPiece( baseTypes::blackPieces ) ) );

/* todo readd code
#ifdef	ENABLE_CHECK_CONSISTENCY
		checkPosConsistency(1);
#endif
*/	
	}
	
	void Position::undoNullMove( void )
	{
		_popState();
		_swapUsThem();

		/* todo readd code
#ifdef ENABLE_CHECK_CONSISTENCY
		checkPosConsistency(0);
#endif
*/
	}
	void Position::doMove( const Move &m )
	{
		assert( m != Move::NOMOVE );
		
		GameState& st = _pushState();
		st.setCurrentMove( m );
		
		const baseTypes::tSquare from = m.getFrom();
		const baseTypes::tSquare to = m.getTo();
		baseTypes::tSquare captureSquare = m.getTo();
		
		const baseTypes::bitboardIndex piece = getPieceAt( from );
		assert( baseTypes::isValidPiece( piece ) );
	/*
	todo readd this code
	bool moveIsCheck = moveGivesCheck(m);
*/
		const baseTypes::bitboardIndex capturedPiece = m.isEnPassantMove() ? ( st.getTurn() ? baseTypes::whitePawns : baseTypes::blackPawns) : getPieceAt( to );
		assert( capturedPiece != baseTypes::separationBitmap );
		assert( capturedPiece != baseTypes::whitePieces );
		assert( capturedPiece != baseTypes::blackPieces );

		st.incrementCounters();
		
		st.clearEpSquare();
		
		// do castle additional instruction
		// todo manage chess960
		if( m.isCastleMove() )
		{
			bool kingSide = to > from;
			
			baseTypes::tSquare rFrom = kingSide ? to + baseTypes::east: to + baseTypes::ovest + baseTypes::ovest;
			baseTypes::tSquare rTo = kingSide ? to + baseTypes::ovest : to + baseTypes::east;
			
			assert( rFrom < baseTypes::squareNumber );
			assert( rTo < baseTypes::squareNumber );
			
			baseTypes::bitboardIndex rook =  getPieceAt( rTo );
			
			assert( rook < baseTypes::bitboardNumber );
			assert( baseTypes::isRook(rook) );
			
			_movePiece( rook, rFrom, rTo );
			st.keyMovePiece( rook, rFrom, rTo);
			
			// todo readd this code
			// st.material += pstValue[rook][rTo] - pstValue[rook][rFrom];
			
			
		}
		
		// do capture
		else if( capturedPiece != baseTypes::empty )
		{
			if( baseTypes::isPawn(capturedPiece) )
			{

				if( m.isEnPassantMove() )
				{
					captureSquare -= MoveGenerator::pawnPush( st.getTurn() );
				}
				assert( captureSquare < baseTypes::squareNumber );
				st.pawnKeyRemovePiece( capturedPiece, captureSquare );
			}
			/*
			todo readd this piece of code
			x.nonPawnMaterial -= nonPawnValue[capture];//[captureSquare];
			*/


			// remove piece
			_removePiece( capturedPiece, captureSquare );
			// update material
			/*
			todo readd this piece of code
			x.material -= pstValue[capture][captureSquare];
			*/

			// update keys
			st.keyRemovePiece( capturedPiece, captureSquare);
			st.materialKeyRemovePiece( capturedPiece, getPieceCount( capturedPiece ) );
		
			// reset fifty move counter
			st.resetFiftyMoveCnt();
		}
		
		// update hashKey
		st.keyMovePiece( piece, from, to );
		_movePiece( piece, from, to );
/*
todo readd this code
		x.material += pstValue[piece][to] - pstValue[piece][from];
	*/

		// Update castle rights if needed
		st.clearCastleRight( _castleRightsMask[ from ] | _castleRightsMask[ to ] );


	if( baseTypes::isPawn( piece ) )
	{
		// double push en passant management
		if(
				MoveGenerator::isPawnDoublePush( from, to )
				// todo cambiare e metterci solo posizioen di pedoni accanto a to.. inutile generare tutti gli attachi per sapere se c'è un pedone
				//&& !( getAttackersTo( (baseTypes::tSquare)( ( from + to ) >> 1 ) ) & _them[ baseTypes::Pawns ] ).isEmpty()
				&& !(BitMapMoveGenerator::getPawnAttack( from + MoveGenerator::pawnPush( st.getTurn() ), ( st.getTurn() == baseTypes::whiteTurn ? baseTypes::white : baseTypes::black )) & getTheirBitmap( baseTypes::Pawns ) ).isEmpty()
		)
		{
			st.addEpSquare( (baseTypes::tSquare)( from + MoveGenerator::pawnPush( st.getTurn() ) ) );
		}
		if( m.isPromotionMove() )
		{
			baseTypes::bitboardIndex promotedPiece = (baseTypes::bitboardIndex)( st.getTurn() + baseTypes::Queens + m.getPromotionType());
			assert ( promotedPiece < baseTypes::bitboardNumber );
			_removePiece( piece, to );
			_addPiece( promotedPiece, to );
/*
todo readd this piece of code
			x.material += pstValue[promotedPiece][to]-pstValue[piece][to];
			x.nonPawnMaterial += nonPawnValue[promotedPiece];//[to];
*/

			st.keyPromotePiece( piece, promotedPiece, to );
			st.pawnKeyRemovePiece( piece, to );
			st.materialKeyPromovePiece( piece,getPieceCount(piece), promotedPiece, getPieceCount(promotedPiece)-1 );
		}
		st.pawnKeyMovePiece( piece, from, to);
		st.resetFiftyMoveCnt();
		
	}
	
	st.setCapturedPiece( capturedPiece );

	st.changeTurn();
	_swapUsThem();
/*


	x.checkers=0;
	if(moveIsCheck)
	{

		if(m.bit.flags != Move::fnone)
		{
			assert(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))<squareNumber);
			x.checkers |= getAttackersTo(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))) & Them[Pieces];
		}
		else
		{
			if(x.checkingSquares[piece] & bitSet(to)) // should be old state, but checkingSquares has not been changed so far
			{
				x.checkers |= bitSet(to);
			}
			if(x.hiddenCheckersCandidate && (x.hiddenCheckersCandidate & bitSet(from)))	// should be old state, but hiddenCheckersCandidate has not been changed so far
			{
				if(!isRook(piece))
				{
					assert(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))<squareNumber);
					x.checkers |= Movegen::attackFrom<Position::whiteRooks>(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove)),bitBoard[occupiedSquares]) & (Them[Queens] |Them[Rooks]);
				}
				if(!isBishop(piece))
				{
					assert(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))<squareNumber);
					x.checkers |= Movegen::attackFrom<Position::whiteBishops>(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove)),bitBoard[occupiedSquares]) & (Them[Queens] |Them[Bishops]);
				}
			}
		}
	}

	calcCheckingSquares();
	assert(getSquareOfThePiece((bitboardIndex)(blackKing-x.nextMove))<squareNumber);
	x.hiddenCheckersCandidate=getHiddenCheckers(getSquareOfThePiece((bitboardIndex)(blackKing-x.nextMove)),x.nextMove);
	assert(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))<squareNumber);
	x.pinnedPieces = getHiddenCheckers(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove)),eNextMove(blackTurn-x.nextMove));
	*/
/* todo readd this code
#ifdef	ENABLE_CHECK_CONSISTENCY
	checkPosConsistency(1);
#endif

*/
	}
	
	
	
	void Position::undoMove( void )
	{
		const GameState& st = getActualStateConst();
		const Move& m = st.getCurrentMove();
		assert( m != Move::NOMOVE );
		const baseTypes::tSquare to = m.getTo();
		const baseTypes::tSquare from = m.getFrom();
		baseTypes::bitboardIndex piece = getPieceAt( to );
		assert( baseTypes::isValidPiece( piece ) );
		
		if( m.isPromotionMove() )
		{
			_removePiece( piece, to);
			piece = isWhitePiece( piece ) ? baseTypes::whitePawns : baseTypes::blackPawns;
			_addPiece( piece, to);
		}
		// todo manage chess960
		else if( m.isCastleMove() )
		{
			bool kingSide = to > from;
			baseTypes::tSquare rFrom = kingSide ? to + baseTypes::east: to + baseTypes::ovest + baseTypes::ovest;
			baseTypes::tSquare rTo = kingSide ? to + baseTypes::ovest : to + baseTypes::east;
			
			assert( rFrom < baseTypes::squareNumber );
			assert( rTo < baseTypes::squareNumber );
			
			baseTypes::bitboardIndex rook =  getPieceAt( rTo );
			
			assert( rook < baseTypes::bitboardNumber );
			assert( baseTypes::isRook(rook) );
			
			_movePiece( rook, rTo, rFrom );
		}
		
		_movePiece( piece, to, from );
		
		assert( st.getCapturedPiece() < baseTypes::bitboardNumber );
		if( st.getCapturedPiece() )
		{
			baseTypes::tSquare capSq = to;
			if( m.isEnPassantMove() )
			{
				capSq += MoveGenerator::pawnPush( st.getTurn() );
			}
			assert( capSq < baseTypes::squareNumber );
			
			_addPiece( st.getCapturedPiece(), capSq );
		}
		
		_popState();
		_swapUsThem();


/*	todo read this code
#ifdef	ENABLE_CHECK_CONSISTENCY
		checkPosConsistency(0);
#endif*/
		
		
	}
	
	void Position::_clearCastleRightsMask(void)
	{
		for( auto& cr : _castleRightsMask )
		{
			cr = baseTypes::noCastleRights;
		}
	}
	
}