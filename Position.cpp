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

namespace libChess
{
	Position::Position()
	{
		_clearStateList();
		
		_getActualState().setTurn( baseTypes::whiteTurn );
		
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
		//assert(s<baseTypes::squareNumber);
		//assert(piece<lastBitboard);
		
		const baseTypes::bitboardIndex MyPieces = getMyPiecesFromPiece(piece);
		// todo check if it's fast enough
		const baseTypes::BitMap b = baseTypes::BitMap::getBitmapFromSquare(s);

		//assert(squares[s]==empty);

		_squares[ s ] = piece;
		_bitBoard[ piece ] += b;
		_bitBoard[ baseTypes::occupiedSquares ] += b;
		_bitBoard[ MyPieces ] += b;
	}
	
	inline void Position::_removePiece(const baseTypes::bitboardIndex piece,const baseTypes::tSquare s)
	{

		//assert(!isKing(piece));
		//assert(s<baseTypes::squareNumber);
		//assert(piece<lastBitboard);
		//assert(squares[s]!=empty);

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
		//assert(from<baseTypes::squareNumber);
		//assert(to<baseTypes::squareNumber);
		//assert(piece<lastBitboard);
		
		//assert(squares[from]!=empty);
		//assert(squares[to]==empty);
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

		if( st.getTurn() == baseTypes::blackTurn )
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
		if( st.getTurn() == baseTypes::blackTurn )
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
		if( st.getTurn() == baseTypes::blackTurn )
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

		s += (st.getTurn() == baseTypes::whiteTurn ? "WHITE TO MOVE" : "BLACK TO MOVE");
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
		
		// todo add this code
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
		bool crEmpty = false;
		

		// todo manage path and masks for castling
		while ( (ss >> token) && !isspace(token) )
		{
			switch(token)
			{
			case 'K':
			{
				const baseTypes::tSquare rsq = baseTypes::H1;
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'Q':
			{
				const baseTypes::tSquare rsq = baseTypes::A1;
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'k':
			{
				const baseTypes::tSquare rsq = baseTypes::H8;
				if ( ( true == crEmpty ) || ( false == _setupCastleRight(rsq) ) )
				{
					return false;
				}
			}
				break;
			case 'q':
			{
				const baseTypes::tSquare rsq = baseTypes::A8;
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
				// todo add this code
				/*if (!(getAttackersTo(x.epSquare) & bitBoard[whitePawns+x.nextMove]))
				{
					st.resetEpSquare();
				}*/
				
			}
			else{
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
			st.setPliesCnt( int( st.getTurn() == baseTypes::blackTurn) );
			st.resetFiftyMoveCnt();
		}
		else
		{
			int plies;
			ss >> plies;
			plies = std::max( 2 * ( plies - 1), 0) + int( st.getTurn() == baseTypes::blackTurn );
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

/*
		// todo readd those methods
		
		calcCheckingSquares();

		x.hiddenCheckersCandidate=getHiddenCheckers(getSquareOfThePiece((bitboardIndex)(blackKing-x.nextMove)),x.nextMove);
		x.pinnedPieces=getHiddenCheckers(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove)),eNextMove(blackTurn-x.nextMove));
		x.checkers= getAttackersTo(getSquareOfThePiece((bitboardIndex)(whiteKing+x.nextMove))) & bitBoard[blackPieces-x.nextMove];



		checkPosConsistency(1);*/
		return true;
	}
	
	bool Position::_setupCastleRight(const baseTypes::tSquare rsq)
	{
	
		GameState &st = _getActualState();
		
		const baseTypes::tSquare ksq = getSquareOfThePiece( baseTypes::whiteKing );
		const baseTypes::tRank kingRank = getRank(ksq);
		const baseTypes::tRank rookRank = getRank(rsq);
		if( kingRank != baseTypes::one && kingRank != baseTypes::eight )
		{
			return false;
		}
		
		if( rookRank != kingRank )
		{
			return false;
		}
		
		if( getPieceAt( rsq ) != baseTypes::whiteRooks )
		{
			return false;
		}
		
		if ( kingRank == baseTypes::one ) 
		{
			if( ksq < rsq )
			{
				if( st.hasCastleRight( baseTypes::wCastleOO ) )
				{
					return false;
				}
				st.setCastleRight( baseTypes::wCastleOO);
			}
			else
			{
				if( st.hasCastleRight( baseTypes::wCastleOOO ) )
				{
					return false;
				}
				st.setCastleRight( baseTypes::wCastleOOO);
			}
		}
		else
		{
			if( ksq < rsq )
			{
				if( st.hasCastleRight( baseTypes::bCastleOO ) )
				{
					return false;
				}
				st.setCastleRight( baseTypes::bCastleOO);
			}
			else
			{
				if( st.hasCastleRight( baseTypes::bCastleOOO) )
				{
					return false;
				}
				st.setCastleRight( baseTypes::bCastleOOO);
			}
		}
	return true;
	}
	
}