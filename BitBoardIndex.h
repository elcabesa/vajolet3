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

#ifndef BITBOARD_INDEX_H_
#define BITBOARD_INDEX_H_


namespace libChess
{
	const char PIECE_NAMES_FEN[] = {' ','K','Q','R','B','N','P',' ',' ','k','q','r','b','n','p',' '};

	enum bitboardIndex
	{
		occupiedSquares = 0,			//0		00000000
		whiteKing = 1,					//1		00000001
		whiteQueens = 2,				//2		00000010
		whiteRooks = 3,					//3		00000011
		whiteBishops = 4,				//4		00000100
		whiteKnights = 5,				//5		00000101
		whitePawns = 6,					//6		00000110
		whitePieces = 7,				//7		00000111

		separationBitmap = 8,
		blackKing = 9,					//9		00001001
		blackQueens = 10,				//10	00001010
		blackRooks = 11,				//11	00001011
		blackBishops = 12,				//12	00001100
		blackKnights = 13,				//13	00001101
		blackPawns = 14,				//14	00001110
		blackPieces = 15,				//15	00001111




		bitboardNumber = 16,

		King = whiteKing,
		Queens,
		Rooks,
		Bishops,
		Knights,
		Pawns,
		Pieces,

		empty = occupiedSquares

	};
	
	static inline bitboardIndex getMyPiecesfromPiece(const bitboardIndex& piece)
	{
		return  piece > separationBitmap ? blackPieces : whitePieces;
	}
	
	static inline bool isValidPiece(const bitboardIndex& piece)
	{
		return  (piece != occupiedSquares) && (piece != whitePieces) && (piece != separationBitmap) && (piece != blackPieces);
	}

	/*	\brief operators for bitboardIndex
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline bitboardIndex& operator++(bitboardIndex& r)
	{
		return r = (bitboardIndex)( (int)r + 1 );
	}

	static inline bitboardIndex& operator--(bitboardIndex& r)
	{
		return r = (bitboardIndex)( (int)r - 1 );
	}

	static inline bitboardIndex operator++(bitboardIndex& r,int)
	{
		bitboardIndex n = r;
		++r;
		return n;
	}

	static inline bitboardIndex operator--(bitboardIndex& r,int)
	{
		bitboardIndex n = r;
		--r;
		return n;
	}

	static inline bitboardIndex operator+(const bitboardIndex d1, const int d2) { return bitboardIndex( (int)d1 + d2 ); }
	static inline bitboardIndex operator-(const bitboardIndex d1, const int d2) { return bitboardIndex( (int)d1 - d2 ); }
	

	inline bitboardIndex& operator+=(bitboardIndex& d1, const int d2) { d1 = d1 + d2; return d1; }
	inline bitboardIndex& operator-=(bitboardIndex& d1, const int d2) { d1 = d1 - d2; return d1; }

	
		/*	\brief class used to iterate over a range of tFile
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	
	class bitboardIndexRange{

	bitboardIndex min;
	bitboardIndex Max;
	public:
	bitboardIndexRange(bitboardIndex _min = bitboardIndex::occupiedSquares, bitboardIndex _Max = bitboardIndex::blackPieces): min(_min), Max( _Max + 1 ){if(Max < min) Max = min;}

	class iterator: public std::iterator<
														std::input_iterator_tag,	// iterator_category
								bitboardIndex,					// value_type
								bitboardIndex,
								const bitboardIndex*,
								bitboardIndex
								>{
			bitboardIndex t;
			public:
				explicit iterator(bitboardIndex _t = bitboardIndex::occupiedSquares) : t(_t) {}
				iterator& operator++() { t += 1; return *this;}
				iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
				bool operator==(iterator other) const { return t == other.t; }
				bool operator!=(iterator other) const { return t != other.t; }
				reference operator*() const {return t;}
		};

	iterator begin() {return iterator(min);}
	iterator end() {return iterator(Max);}

	};
	
	enum eTurn	// color turn. ( it's also used as offset to access bitmaps by index)
	{
		whiteTurn = 0,
		blackTurn = (int)blackKing - (int)whiteKing
	};
	
	inline eTurn getSwitchedTurn(eTurn t)
	{
		return (eTurn)(blackTurn - t);
	}

	enum eCastle	// castleRights
	{
		wCastleOO=1,
		wCastleOOO=2,
		bCastleOO=4,
		bCastleOOO=8,
	};
	
}
#endif