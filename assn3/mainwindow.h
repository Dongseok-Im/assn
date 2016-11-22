#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "BoardWidget.h"
#include <QtWidgets>
#include<stdlib.h>
#include<time.h>





class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void SetClickPos(int x, int y) { Index_x = (x-135) / BLOCKSIZE; Index_y = (y-40) / BLOCKSIZE; }
	int GetIndex_x() { return Index_x; }
	int GetIndex_y() { return Index_y; }
	
private:
	BoardWidget *board; /// puzzle board
	CurrentWidget *current; // current  widget�� ���
	Ui::MainWindowClass ui;

	QPushButton* newGame; //���ο� ������ ����
	QPushButton* nextPiece; //���� ����ִ� ������ �𸣸� �н��� �ٲٴ� ��


	QTimer* timer;
	void initMenus(void);
	void initWidgets(void);
	

	int Index_x, Index_y;
	int endGame; //�ϼ��� Ȯ��

	void mousePressEvent(QMouseEvent *event) {
		int x = event->x(); int y = event->y();
		if (x >= 135 && y >= 40)
			SetClickPos(x, y);

		endGame = 0; //�ϼ��� Ȯ��

		//���⼭ ���� ��
		if (GameStart == 1 && (Index_x >= 0 && Index_x <= 3) && (Index_y >= 0 && Index_y <= 3)) //���⼭ ������ ������ ����Ѵ�.
		{
			board->GetBoardGame()->AnswerCheck(current->GetCurrentP(), Index_y, Index_x);

			if (current->GetCurrentP()->GetId() == 0) //������ ��� ���� �ǽ��� �����.
			{
				for (int i = 0; i < BOARDSIZE; i++) {
					for (int j = 0; j < BOARDSIZE; j++) {
						current->GetCurrentLabels(i, j)->clear();
						current->GetCurrentLabels(i, j)->show();
					}
				}
			}

			for (int i = 0; i < BOARDSIZE; i++) {
				for (int j = 0; j < BOARDSIZE; j++) {
					if (board->GetBoardGame()->Getblk(i, j).GetBlockMarked() == 1)
					{
						QPixmap buffer = QPixmap::fromImage(*board->GetblockImages(i, j));
						board->GetblockLabels(i, j)->setPixmap(buffer);
						board->GetblockLabels(i, j)->resize(BLOCKSIZE, BLOCKSIZE);
						board->GetblockLabels(i, j)->move(BLOCKSIZE*j, BLOCKSIZE*i);
						board->GetblockLabels(i, j)->show();
						
						endGame++; //�ϼ��� Ȯ��
					}

				}
			}

			if (endGame == 16) //������ ��� ���� ���
			{
				QMessageBox msgBox;
				msgBox.setWindowTitle("Congratualtion!!");
				msgBox.setText("You win the game!!");
				msgBox.exec();

			}

		}

	

		return;
	}


	bool ImageOpen;
	bool GameStart;
	int randomindex;




private slots: //�� Event drive�� �� �� �ִ�.
	void onTimer(void);
	void loadImage(void);
	bool imageViewer(QString file);
	void newGameSlot(void);
	void nextPieceSlot(void);
};

#endif // MAINWINDOW_H
