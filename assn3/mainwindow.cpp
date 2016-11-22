#pragma once
#include "mainwindow.h"
#include <QMenu>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);

	
	initMenus();
	initWidgets();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer->start(1000);

	ImageOpen = 0;
	GameStart = 0;
	srand(time(NULL));
	
}

void MainWindow::onTimer() {
//	QMessageBox::about(0, "Alram", "tic tock");
}

void MainWindow::initMenus() {
	// file menu construction
	QMenu *fileMenu = new QMenu(tr("file(&F)"));
	
	// Open Image
	fileMenu->addAction(tr("Open Image(&O)"), this, SLOT(loadImage()),
		QKeySequence(QKeySequence::New)); //loadImage()�� �� File open�� �� �ϰ� ������ �� this�� mainwindow���� LoadImage�� �ҷ����� ��
	// Quit
	fileMenu->addAction(tr("Quit(&Q)"), this, SLOT(close()),
		QKeySequence(tr("Ctrl+Q")));

	// add "file" menu on menu bar
	menuBar()->addMenu(fileMenu);
}


void MainWindow::initWidgets() {
	
	//board initialization
	board = new BoardWidget();
	current = new CurrentWidget();

	//layout initialization
	QVBoxLayout* vbox=new QVBoxLayout();
	QHBoxLayout* hbox=new QHBoxLayout();
	
	newGame = new QPushButton("new game",this); 
	nextPiece = new QPushButton("next Piece",this);
	connect(newGame, SIGNAL(clicked()), this, SLOT(newGameSlot()));
	connect(nextPiece, SIGNAL(clicked()), this, SLOT(nextPieceSlot()));

	vbox->addWidget(newGame);
	vbox->addWidget(current);
	vbox->addWidget(nextPiece);

	hbox->addLayout(vbox);
	hbox->addWidget(board);
	
	QWidget *widget = new QWidget();
	widget->setLayout(hbox);
	setCentralWidget(widget);
	
	// ���� â ũ�� ����
	layout()->setSizeConstraint(QLayout::SetFixedSize);

}


MainWindow::~MainWindow()
{

}

bool MainWindow::imageViewer(QString file)
{	
	QImage tmp, scaled_tmp;

	if (tmp.load(file)) {
		scaled_tmp = tmp.scaled(300, 300);

		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {

				QRect rect(BLOCKSIZE*j, BLOCKSIZE*i, BLOCKSIZE, BLOCKSIZE); //BoardWidget �������� Block size�� �ڸ� �غ�
				QPixmap buffer = QPixmap::fromImage(scaled_tmp); //�ڸ�
				QPixmap cropped = buffer.copy(rect);

				*(board->GetblockImages(i, j)) = scaled_tmp.copy(rect); // ������ �̹����� QImage ������ ����
				board->GetblockLabels(i, j)->setPixmap(cropped); 
				board->GetblockLabels(i, j)->resize(BLOCKSIZE, BLOCKSIZE);
				board->GetblockLabels(i, j)->move(BLOCKSIZE*j, BLOCKSIZE*i);
				board->GetblockLabels(i, j)->show();
			}
		}

		return true;

	}
	else
	{
		QMessageBox::about(0, "load error", "Re-load");
		return false;
	}

	


}
void MainWindow::loadImage() {

	QFileDialog fileDialog(this, "Open File",
		"C:\\", "Image (*.bmp *.png *.jpeg *.jpg)");
	QStringList fileNames;
	if (fileDialog.exec()) {
		fileNames = fileDialog.selectedFiles();
	}
	QString selectedFile; //���� �ϳ��� ����
	for (int nIndex = 0; nIndex < fileNames.size(); nIndex++)
	{
		selectedFile.append(fileNames.at(nIndex));
	}
 	ImageOpen = imageViewer(selectedFile); //imageViewer�� ��������
	
	board->GetBoardGame()->resetblkMark(); //Block�� Mark �ʱ�ȭ
	for (int i = 0; i < 4; i++)
		board->GetBoardGame()->Getp(i)->SetId(i + 1);	//Piece�� Id �ʱ�ȭ
	GameStart = 0; //Gamestart ��ư �ʱ�ȭ

}

void MainWindow::newGameSlot(){

	if (ImageOpen == 0)
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Error");
		msgBox.setText("Open the Image, Please");
		msgBox.exec();
	}
	else
	{
		if (GameStart == 1) //Game ���߿� New game Start�� ������ �ʱ�ȭ
		{
			board->GetBoardGame()->resetblkMark(); //Block�� Mark �ʱ�ȭ
		
			for (int i = 0; i < 4; i++)
			board->GetBoardGame()->Getp(i)->SetId(i+1);	//Piece�� Id �ʱ�ȭ
		}

		GameStart = 1;

		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				board->GetblockLabels(i, j)->clear();
				board->GetblockLabels(i, j)->show();
				current->GetCurrentLabels(i, j)->clear();
				current->GetCurrentLabels(i, j)->show();
			}
		}


		randomindex= rand() % 4;
		current->SetCurrentP(board->GetBoardGame(),randomindex);

		switch (current->GetType()) //�������� �����ִ� �ڵ� �����ƾƾƾƾƾӾƾƾƾƾƾƾ�
		{

		case ITYPE:
			if (current->GetCurrentRot() == 0)
			{
				for (int i = current->GetCurrentCy(); i < current->GetCurrentCy() + 4; i++)
				{
					QImage tmp;
					tmp = board->GetblockImages(i, current->GetCurrentCx())->scaled(CURRENTSIZE, CURRENTSIZE);
					
					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(i, 2)->setPixmap(buffer);
					current->GetCurrentLabels(i, 2)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(i, 2)->move(CURRENTSIZE*2, CURRENTSIZE * i);
					current->GetCurrentLabels(i, 2)->show();
				}
			}
			break;
			
		case TTYPE:
			if (current->GetCurrentRot() == 2)
			{
				for (int j = current->GetCurrentCx()-1; j <= current->GetCurrentCx() + 1; j++)
				{
					QImage tmp;
					tmp = board->GetblockImages(0, j)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(1, j)->setPixmap(buffer);
					current->GetCurrentLabels(1, j)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(1, j)->move(CURRENTSIZE * j, CURRENTSIZE * 1);
					current->GetCurrentLabels(1, j)->show();
				}
				QImage tmp;
				tmp = board->GetblockImages(1,2)->scaled(CURRENTSIZE, CURRENTSIZE);

				QPixmap buffer = QPixmap::fromImage(tmp);
				current->GetCurrentLabels(2, 2)->setPixmap(buffer);
				current->GetCurrentLabels(2, 2)->resize(CURRENTSIZE, CURRENTSIZE);
				current->GetCurrentLabels(2, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * 2);
				current->GetCurrentLabels(2, 2)->show();
			

			}
			else if (current->GetCurrentRot() == 3)
			{
				for (int i = current->GetCurrentCy() - 1; i <= current->GetCurrentCy() + 1; i++)
				{
					QImage tmp;
					tmp = board->GetblockImages(i, 1)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(i, 2)->setPixmap(buffer);
					current->GetCurrentLabels(i, 2)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(i, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * i);
					current->GetCurrentLabels(i, 2)->show();
				}
				QImage tmp;
				tmp = board->GetblockImages(2, 2)->scaled(CURRENTSIZE, CURRENTSIZE);

				QPixmap buffer = QPixmap::fromImage(tmp);
				current->GetCurrentLabels(2, 3)->setPixmap(buffer);
				current->GetCurrentLabels(2, 3)->resize(CURRENTSIZE, CURRENTSIZE);
				current->GetCurrentLabels(2, 3)->move(CURRENTSIZE * 3, CURRENTSIZE * 2);
				current->GetCurrentLabels(2, 3)->show();


			}
			break;
			
		case JTYPE:
			if (current->GetCurrentRot() == 1)
			{
				for (int i = current->GetCurrentCy(); i >= current->GetCurrentCy() - 2; i--)
				{
					QImage tmp;
					tmp = board->GetblockImages(i, 3)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(i-1, 2)->setPixmap(buffer);
					current->GetCurrentLabels(i-1, 2)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(i-1, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * (i-1));
					current->GetCurrentLabels(i-1, 2)->show();
				}
				QImage tmp;
				tmp = board->GetblockImages(3, 2)->scaled(CURRENTSIZE, CURRENTSIZE);

				QPixmap buffer = QPixmap::fromImage(tmp);
				current->GetCurrentLabels(2, 1)->setPixmap(buffer);
				current->GetCurrentLabels(2, 1)->resize(CURRENTSIZE, CURRENTSIZE);
				current->GetCurrentLabels(2, 1)->move(CURRENTSIZE * 1, CURRENTSIZE * 2);
				current->GetCurrentLabels(2, 1)->show();

			}

			break;
	
		}


	}
	
}

void MainWindow::nextPieceSlot() {
	
	if (endGame != 16) //Game�� �ȳ�������
	{
		if (ImageOpen == 0)
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("Error");
			msgBox.setText("Open the Image, Please");
			msgBox.exec();
		}
		else if (ImageOpen != 0 && GameStart == 0)
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("Error");
			msgBox.setText("Press the New Game, Please");
			msgBox.exec();
		}

		else
		{
			for (int i = 0; i < BOARDSIZE; i++) {
				for (int j = 0; j < BOARDSIZE; j++) {
					current->GetCurrentLabels(i, j)->clear();
					current->GetCurrentLabels(i, j)->show();
				}
			}

			if (randomindex <= 2)
				randomindex += 1;

			else if (randomindex == 3)
				randomindex = 0;

			current->SetCurrentP(board->GetBoardGame(), randomindex);

			switch (current->GetType())
			{

			case ITYPE:
				if (current->GetCurrentRot() == 0)
				{
					for (int i = current->GetCurrentCy(); i < current->GetCurrentCy() + 4; i++)
					{
						QImage tmp;
						tmp = board->GetblockImages(i, current->GetCurrentCx())->scaled(CURRENTSIZE, CURRENTSIZE);

						QPixmap buffer = QPixmap::fromImage(tmp);
						current->GetCurrentLabels(i, 2)->setPixmap(buffer);
						current->GetCurrentLabels(i, 2)->resize(CURRENTSIZE, CURRENTSIZE);
						current->GetCurrentLabels(i, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * i);
						current->GetCurrentLabels(i, 2)->show();
					}
				}
				break;

			case TTYPE:
				if (current->GetCurrentRot() == 2)
				{
					for (int j = current->GetCurrentCx() - 1; j <= current->GetCurrentCx() + 1; j++)
					{
						QImage tmp;
						tmp = board->GetblockImages(0, j)->scaled(CURRENTSIZE, CURRENTSIZE);

						QPixmap buffer = QPixmap::fromImage(tmp);
						current->GetCurrentLabels(1, j)->setPixmap(buffer);
						current->GetCurrentLabels(1, j)->resize(CURRENTSIZE, CURRENTSIZE);
						current->GetCurrentLabels(1, j)->move(CURRENTSIZE * j, CURRENTSIZE * 1);
						current->GetCurrentLabels(1, j)->show();
					}
					QImage tmp;
					tmp = board->GetblockImages(1, 2)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(2, 2)->setPixmap(buffer);
					current->GetCurrentLabels(2, 2)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(2, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * 2);
					current->GetCurrentLabels(2, 2)->show();


				}
				else if (current->GetCurrentRot() == 3)
				{
					for (int i = current->GetCurrentCy() - 1; i <= current->GetCurrentCy() + 1; i++)
					{
						QImage tmp;
						tmp = board->GetblockImages(i, 1)->scaled(CURRENTSIZE, CURRENTSIZE);

						QPixmap buffer = QPixmap::fromImage(tmp);
						current->GetCurrentLabels(i, 2)->setPixmap(buffer);
						current->GetCurrentLabels(i, 2)->resize(CURRENTSIZE, CURRENTSIZE);
						current->GetCurrentLabels(i, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * i);
						current->GetCurrentLabels(i, 2)->show();
					}
					QImage tmp;
					tmp = board->GetblockImages(2, 2)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(2, 3)->setPixmap(buffer);
					current->GetCurrentLabels(2, 3)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(2, 3)->move(CURRENTSIZE * 3, CURRENTSIZE * 2);
					current->GetCurrentLabels(2, 3)->show();


				}
				break;

			case JTYPE:
				if (current->GetCurrentRot() == 1)
				{
					for (int i = current->GetCurrentCy(); i >= current->GetCurrentCy() - 2; i--)
					{
						QImage tmp;
						tmp = board->GetblockImages(i, 3)->scaled(CURRENTSIZE, CURRENTSIZE);

						QPixmap buffer = QPixmap::fromImage(tmp);
						current->GetCurrentLabels(i - 1, 2)->setPixmap(buffer);
						current->GetCurrentLabels(i - 1, 2)->resize(CURRENTSIZE, CURRENTSIZE);
						current->GetCurrentLabels(i - 1, 2)->move(CURRENTSIZE * 2, CURRENTSIZE * (i - 1));
						current->GetCurrentLabels(i - 1, 2)->show();
					}
					QImage tmp;
					tmp = board->GetblockImages(3, 2)->scaled(CURRENTSIZE, CURRENTSIZE);

					QPixmap buffer = QPixmap::fromImage(tmp);
					current->GetCurrentLabels(2, 1)->setPixmap(buffer);
					current->GetCurrentLabels(2, 1)->resize(CURRENTSIZE, CURRENTSIZE);
					current->GetCurrentLabels(2, 1)->move(CURRENTSIZE * 1, CURRENTSIZE * 2);
					current->GetCurrentLabels(2, 1)->show();

				}
				break;

			}

		}

	}
	

}
	
