#include "Board.h"

Board::Board()
{
	GenPiece();
	GenAnswer();
}

Board::~Board()
{
//	delete p;
}

void Board::GenPiece() {
	p[0] = new Ipiece;
	p[1] = new Tpiece;
	p[2] = new Tpiece;
	p[3] = new Jpiece;
	
}

void Board::GenAnswer() {

	blk[0][0].SetAnswerId(1);
	blk[1][0].SetAnswerId(1);
	blk[2][0].SetAnswerId(1);
	blk[3][0].SetAnswerId(1);
	p[0]->SetId(1);
	p[0]->SetRotate(0);
	p[0]->SetCx(0);
	p[0]->SetCy(0);

	blk[0][1].SetAnswerId(2);
	blk[0][2].SetAnswerId(2);
	blk[0][3].SetAnswerId(2);
	blk[1][2].SetAnswerId(2);
	p[1]->SetId(2);
	p[1]->SetRotate(2);
	p[1]->SetCx(2);
	p[1]->SetCy(0);

	blk[1][1].SetAnswerId(3);
	blk[2][1].SetAnswerId(3);
	blk[2][2].SetAnswerId(3);
	blk[3][1].SetAnswerId(3);
	p[2]->SetId(3);
	p[2]->SetRotate(3);
	p[2]->SetCx(1);
	p[2]->SetCy(2);


	blk[3][2].SetAnswerId(4);
	blk[1][3].SetAnswerId(4);
	blk[2][3].SetAnswerId(4);
	blk[3][3].SetAnswerId(4);
	p[3]->SetId(4);
	p[3]->SetRotate(1);
	p[3]->SetCx(2);
	p[3]->SetCy(3);

}

void Board::AnswerCheck(Piece *CurrentP, int i, int j)
{
	if (CurrentP->GetId() == blk[i][j].GetAnswerId())
	{
		for (int k = 0; k < 4; k++)
			for (int l = 0; l < 4; l++)
				if (blk[i][j].GetAnswerId() == blk[k][l].GetAnswerId())
				{
					blk[k][l].SetBlockMarked(1);
				}

				
		CurrentP->SetId(0); //¸ÂÃá °æ¿ì
	}
	
		

}

void Board::resetblkMark()
{
	for (int k = 0; k < 4; k++)
		for (int l = 0; l < 4; l++)	
			blk[k][l].SetBlockMarked(0);
	
}


/*switch (CurrentP->GetType())
	{
	case ITYPE:
		Piece *CurrentP = new Ipiece;
		
		
		break;
		}*/