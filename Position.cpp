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
#include <sstream>
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
	
	
	inline void Position::_clear()
	{
		for (auto& piece : _squares)
		{
			piece = empty;
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
	
	
	HashKey Position::_calcKey(void) const
	{
		HashKey hash;
		const GameState& st = getActualStateConst();

		for(auto t: tSquareRange())
		{
			if( _squares[t] != empty )
			{
				hash.addPiece( _squares[t], t );
			}
		}

		if( st.getTurn() == blackTurn )
		{
			hash.changeSide();
		}
		
		hash.changeCastlingRight( st.getCastleRights() );

		tSquare epSq = st.getEpSquare();
		if( epSq != squareNone )
		{
			hash.addEp(epSq);
		}

		return hash;
	}
	

	HashKey Position::_calcPawnKey(void) const
	{
		HashKey hash(1);
		
		for(const auto t : getBitmap( whitePawns ) )
		{
			hash.addPiece( whitePawns, t );
		}
		
		for(const auto t : getBitmap( blackPawns ) )
		{
			hash.addPiece( blackPawns, t );
		}
		return hash;
	}


	HashKey Position::_calcMaterialKey(void) const
	{
		HashKey hash;
		for( const auto p: bitboardIndexRange())
		{
			if ( isValidPiece(p) )
			{
				for ( unsigned int cnt = 0; cnt < getPieceCount( p ); ++cnt )
				{
					hash.addPiece( p, (tSquare)cnt );
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
		for( const auto rank: tRankNegativeRange() )
		{
			unsigned int emptyFiles = 0u;
			// for ech file
			for( const auto file: tFileRange() )
			{
				const tSquare sq = getSquareFromFileRank( file, rank );
				const bitboardIndex piece = getPieceAt( sq );
				
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
			if( rank != tRank::one )
			{
				s += "/";
			}
		}
		
		
		// turn
		s += " ";
		if( st.getTurn() == blackTurn )
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
		for( const auto rank: tRankRange() )
		{
			unsigned int emptyFiles = 0u;
			// for ech file
			for( const auto file: tFileRange() ) 
			{
				const tSquare sq =getSquareFromFileRank( file, rank );
				const bitboardIndex piece = getPieceAt( sq );
				
				// write piece...
				if( isValidPiece(piece) )
				{
					// ...prepending empty square number
					if( emptyFiles != 0 )
					{
						s += std::to_string( emptyFiles );
					}
					emptyFiles = 0u;
					
					bitboardIndex symPiece = piece;
					if( isBlackPiece( symPiece ) )
					{
						symPiece -= separationBitmap;
					}
					else
					{
						symPiece += separationBitmap;
					}
					s += getPieceName( symPiece );
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
			if( rank != tRank::one )
			{
				s += "/";
			}
		}
		
		// turn
		s += " ";
		if( st.getTurn() == blackTurn )
		{
			s += "w";
		}
		else
		{
			s += "b";
		}
		s += " ";
		
		// castling rights
		symmSt.clearAllCastleRights();
		if( st.hasCastleRight( wCastleOO ) ) symmSt.setCastleRight(  bCastleOO );
		if( st.hasCastleRight( wCastleOOO ) ) symmSt.setCastleRight(  bCastleOOO );
		if( st.hasCastleRight( bCastleOO ) ) symmSt.setCastleRight(  wCastleOO );
		if( st.hasCastleRight( bCastleOOO ) ) symmSt.setCastleRight(  wCastleOOO );
		s += symmSt.getCastleRightsString();
		
		s += " ";
		// epsquare
		const tSquare sq = st.getEpSquare();
		const tFile symFile = getFile(sq);
		tRank symRank = tRank::eight - getRank(sq);
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
		
		for( const auto rank: tRankNegativeRange() )
		{
			s += "  +---+---+---+---+---+---+---+---+\n";
			s += to_string(rank) +  " |";
			
			for( const auto file: tFileRange() )
			{
				const tSquare sq =getSquareFromFileRank( file, rank );
				const bitboardIndex piece = getPieceAt( sq );
				s += " " + getPieceName( piece ) + " |";
			}
			s += "\n";
			
		}
		s += "  +---+---+---+---+---+---+---+---+\n";
		s += " ";
		for(auto file: tFileRange())
		{
			s += "   " + to_string(file);
		}
		s += "\n";

		s += (st.getTurn() == whiteTurn ? "WHITE TO MOVE" : "BLACK TO MOVE");
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
		tSquare sq = A8;
		tFile file = A;
		
		std::istringstream ss(fenStr);
		ss >> std::noskipws;
		
		_clear();
		
		GameState &st = _getActualState();

		// parse piece list
		while( (ss >> token) && !std::isspace(token) )
		{
			
			//std::cout<<to_string(sq)<<std::endl;
			
			if(token == '/')
			{
				
				sq -= tSquare(16);
				//std::cout<<"a capo "<<to_string(sq)<<std::endl;
				file = A;
				if( file < A || file > H || sq > H8 || sq < A1 )
				{
					//std::cout<<"argh 1"<<std::endl;
					return false;
				}
				
			}else if( isdigit(token) )
			{
				sq += tSquare( token - '0' ); // Advance the given number of files
				file += tFile( token - '0' );
				
				/*if( file < A || file > H || sq > H8 || sq < A1 )
				{
					//std::cout<<"argh 2"<<std::endl;
					return false;
				}*/
			} 
			else
			{
				if( file < A || file > H || sq > H8 || sq < A1 )
				{
					//std::cout<<"argh 3"<<std::endl;
					return false;
				}
				// TODO try to use a function here that map char to index -> using PIECE_NAMES_FEN in bitBoardIndex.h
				switch(token)
				{
				case 'P':
					_addPiece( whitePawns, sq );
					break;
				case 'N':
					_addPiece( whiteKnights, sq );
					break;
				case 'B':
					_addPiece( whiteBishops, sq );
					break;
				case 'R':
					_addPiece( whiteRooks, sq );
					break;
				case 'Q':
					_addPiece( whiteQueens, sq );
					break;
				case 'K':
					_addPiece( whiteKing, sq );
					break;
				case 'p':
					_addPiece( blackPawns, sq );
					break;
				case 'n':
					_addPiece( blackKnights, sq );
					break;
				case 'b':
					_addPiece( blackBishops, sq );
					break;
				case 'r':
					_addPiece( blackRooks, sq );
					break;
				case 'q':
					_addPiece( blackQueens, sq );
					break;
				case 'k':
					_addPiece( blackKing, sq );
					break;
				default:
					return false;
				
				}
				sq++;
			}
			
		}
		if( sq != A2 )
		{
			std::cout<<"argh 4"<< to_string(sq) << std::endl;
			return false;
		}
		
		std::cout<<"get turn"<< std::endl;
		// turn
		ss >> token;
		if( token == 'w' )
		{
			std::cout<<"white turn"<< std::endl;
			st.setTurn(whiteTurn);
		}
		else if( token == 'b' )
		{
			std::cout<<"black turn"<< std::endl;
			st.setTurn(blackTurn);
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
		
		std::cout<<"get castle"<< std::endl;
		// castle rights
		st.clearAllCastleRights();
		unsigned int crCounter = 0;
		
		while ( (ss >> token) && !isspace(token) )
		{
			switch(token)
			{
			case 'K':
				++crCounter;
				std::cout<<"wOO"<< std::endl;
				st.setCastleRight( wCastleOO );
				break;
			case 'Q':
				++crCounter;
				std::cout<<"wOOO"<< std::endl;
				st.setCastleRight( wCastleOOO);
				break;
			case 'k':
				++crCounter;
				std::cout<<"bOO"<< std::endl;
				st.setCastleRight( bCastleOO);
				break;
			case 'q':
				++crCounter;
				std::cout<<"bOOO"<< std::endl;
				st.setCastleRight( bCastleOOO);
				break;
			case '-':
				break;
			default:
				return false;
			}
		}
		
		if( crCounter > 4 || (crCounter == 0 && st.getCastleRights() != 0 ) )
		{
			return false;
		}
		
		std::cout<<"get ep"<< std::endl;
		ss >> token;
		
		// parse epsquare
		if( token == '-' )
		{
			std::cout<<"ep null"<< std::endl;
			st.setEpSquare( squareNone );
		}
		else
		{
			
			std::cout<<"ep "<< std::endl;
			char col,row;
			if (
				( (ss >> col) && (col >= 'a' && col <= 'h') )
				&& ( (ss >> row) && ( row == '3' || row == '6' ) )
				)
			{
				st.setEpSquare( (tSquare) ( ( col - 'a' ) + 8 * ( row - '1' ) ) );
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
		std::cout<<"get fifty"<< std::endl;
		int fmc;
		ss >> std::skipws >> fmc;
		st.setFiftyMoveCnt(fmc);
		
		if( ss.eof() )
		{
			st.setPliesCnt( int( st.getTurn() == blackTurn) );
			st.resetFiftyMoveCnt();

		}else
		{
			int plies;
			ss >> plies;
			plies = std::max( 2 * ( plies - 1), 0) + int( st.getTurn() == blackTurn );
			st.setPliesCnt( plies );
			
		}
		
		st.resetCountersNullMove();
		st.setCurrentMove( NOMOVE );
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
	
}