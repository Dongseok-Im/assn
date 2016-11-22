#pragma once
#include"Block.h"
#include"Piece.h"

using namespace std;

class Board
{
public:
	//GetImage();
	//	void SetImage(); // 보드를 출력.
	Board();
	~Board();
	void GenAnswer();
	void AnswerCheck(Piece *p,int i, int j);
	void resetblkMark();
	void GenPiece();
	Block Getblk(int i, int j) { return blk[i][j]; }
	Piece* Getp(int i) { return p[i]; }
//	void Setblk(Block blk[4][4], int i, int j) { this->blk[i][j] = blk[i][j]; }

private:
	Block blk[4][4];
	Piece *p[4];
	int Id;
};

