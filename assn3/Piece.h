#pragma once
#include<iostream>

enum Piecetype { ITYPE = 1, OTYPE, LTYPE, JTYPE, STYPE, TTYPE, ZTYPE }; //�ǽ��� ���� enum Ÿ�� ����

class Piece //�̳� draw�� Ŀ��Ʈ �ǽ��� ��� setdraw(x,y,rotat)�� ��ǥ�� set //darw�� �̳��� �׸��°� 1�ڷ�
{
public:   //pure virtual type���� �����Ͽ�, ������ Ipiece, Lpiece ��, Ư�� Piece�� Polymorphism�� �̿��Ͽ� �����ͷ� ����Ű�� ��
	virtual int GetId() = 0;  //Piece�� Id�� get�Ͽ� piece�� Id�� blk�� id�� ���Ͽ� ������ ���� ��ȹ
	virtual int GetType() = 0; //Piece�� type�� get��
	virtual void SetId(int Id) = 0;
	virtual int GetRotate() = 0; //piece�� ȸ�� ������ get��
	virtual void SetRotate(int Rotate) = 0;
	virtual int GetCx() = 0; //Piece�� x��ǥ�� get��
	virtual void SetCx(int Cx) = 0;
	virtual int GetCy() = 0; //Piece�� y��ǥ�� get��
	virtual void SetCy(int Cy) = 0;
	virtual void SetImage(int Cx, int Cy, int Rotate) = 0;
	virtual void Draw() = 0;
private:


};

class Ipiece : public Piece //Ipiece�� Piece�� ��ӹ޾� ����
{
public:
	Ipiece() { Type = ITYPE; Id = 0; Rotate = 0; } // Ipiece �ʱ�ȭ
	virtual int GetId() { return Id; }
	virtual int GetType() { return Type; }
	virtual void SetId(int Id) { this->Id = Id; }
	virtual int GetRotate() { return Rotate; }
	virtual void SetRotate(int Rotate) { this->Rotate = Rotate; }
	virtual int GetCx() { return Cx; }
	virtual void SetCx(int Cx) { this->Cx = Cx; }
	virtual int GetCy() { return Cy; }
//	virtual void SetCy(int Cy) { this->Cy = Cy; }
//	virtual void SetImage(int Cx, int Cy, int Rotate);
	//=operator(A) {���� �ϰ� ��}

private:
	int Type;
	int Id;
	int Rotate;
	int Cx;
	int Cy;

};

class Tpiece : public Piece
{
public:
	Tpiece() { Type = TTYPE; Id = 0; Rotate = 0; }
	virtual int GetId() { return Id; }
	virtual int GetType() { return Type; }
	virtual void SetId(int Id) { this->Id = Id; }
	virtual int GetRotate() { return Rotate; }
	virtual void SetRotate(int Rotate) { this->Rotate = Rotate; }
	virtual int GetCx() { return Cx; }
	virtual void SetCx(int Cx) { this->Cx = Cx; }
	virtual int GetCy() { return Cy; }
	virtual void SetCy(int Cy) { this->Cy = Cy; }

private:
	int Type;
	int Id;
	int Rotate;
	int Cx;
	int Cy;
};

class Jpiece : public Piece
{
public:
	Jpiece() { Type = JTYPE; Id = 0; Rotate = 0; }
	virtual int GetId() { return Id; }
	virtual int GetType() { return Type; }
	virtual void SetId(int Id) { this->Id = Id; }
	virtual int GetRotate() { return Rotate; }
	virtual void SetRotate(int Rotate) { this->Rotate = Rotate; }
	virtual int GetCx() { return Cx; }
	virtual void SetCx(int Cx) { this->Cx = Cx; }
	virtual int GetCy() { return Cy; }
	virtual void SetCy(int Cy) { this->Cy = Cy; }

private:
	int Type;
	int Id;
	int Rotate;
	int Cx;
	int Cy;
};