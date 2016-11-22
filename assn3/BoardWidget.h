#pragma once
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "Board.h"

#define PUZZLE_SIZE 4
#define BLOCKSIZE 75
#define BOARDSIZE 4
#define CURRENTSIZE 30
// Erase this fixed definition

class BoardWidget : public QWidget
{
	Q_OBJECT
private:
	QLabel* blockLabels[BOARDSIZE][BOARDSIZE]; // Qlabel로 배경화면을 지정
	QImage* blockImages[BOARDSIZE][BOARDSIZE]; // QImage로 사진을 저장
	Board BoardGame; //Board 클래스의 객체로, 여기에 piece 정보와, 정답 정보 등을 담고 있다.

	



public:
	BoardWidget(QWidget *parent =0)
	: QWidget(parent){
	
		setMouseTracking(true); 

		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				blockLabels[i][j] = new QLabel(this);
				blockLabels[i][j]->resize(BLOCKSIZE,BLOCKSIZE);
				blockLabels[i][j]->move(BLOCKSIZE*j, BLOCKSIZE*i);
				blockLabels[i][j]->setStyleSheet("QLabel { background-color: black ; border: 1px solid white}");
				blockLabels[i][j]->show();

				blockImages[i][j] = new QImage();
			}
		}

		// 위젯 크기 고정
		setFixedSize(300, 300);
		

	};

	~BoardWidget() {
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				delete blockLabels[i][j];
			}
		}
	};


	QLabel* GetblockLabels(int i,int j) { return blockLabels[i][j]; }
	QImage* GetblockImages(int i, int j) { return blockImages[i][j]; }
	Board* GetBoardGame() { return &BoardGame; }
	

	

};


class CurrentWidget : public QWidget
{
	Q_OBJECT
private:
	QLabel* CurrentLabels[BOARDSIZE][BOARDSIZE];
	QImage* CurrentImages[BOARDSIZE][BOARDSIZE];
	Piece* CurrentP;
	

public:
	CurrentWidget(QWidget *parent = 0)
		: QWidget(parent) {

		setMouseTracking(true);

		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				CurrentLabels[i][j] = new QLabel(this);
				CurrentLabels[i][j]->resize(CURRENTSIZE, CURRENTSIZE);
				CurrentLabels[i][j]->move(CURRENTSIZE*j, CURRENTSIZE*i);
				CurrentLabels[i][j]->setStyleSheet("");
				CurrentLabels[i][j]->show();

			}
		}

		// 위젯 크기 고정
		setFixedSize(CURRENTSIZE*4, CURRENTSIZE*4);


	};
	~CurrentWidget() {
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				delete CurrentLabels[i][j];
			}
		}
	};

	void SetCurrentP(Board* BoardGame,int &randomindex);
	Piece* GetCurrentP() { return CurrentP; }
	int GetCurrentCx() { return CurrentP->GetCx(); }
	int GetCurrentCy() { return CurrentP->GetCy(); }
	int GetCurrentRot() { return CurrentP->GetRotate(); }
	int GetType() { return CurrentP->GetType(); }
	QLabel* GetCurrentLabels(int i, int j) { return CurrentLabels[i][j]; }

};
