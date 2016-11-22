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
	QLabel* blockLabels[BOARDSIZE][BOARDSIZE]; // Qlabel�� ���ȭ���� ����
	QImage* blockImages[BOARDSIZE][BOARDSIZE]; // QImage�� ������ ����
	Board BoardGame; //Board Ŭ������ ��ü��, ���⿡ piece ������, ���� ���� ���� ��� �ִ�.

	



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

		// ���� ũ�� ����
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

		// ���� ũ�� ����
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
