#pragma once
#include<iostream>

enum Piecetype { ITYPE = 1, OTYPE, LTYPE, JTYPE, STYPE, TTYPE, ZTYPE }; //피스에 따른 enum 타입 설정

class Piece //이놈 draw는 커런트 피스를 출력 setdraw(x,y,rotat)는 좌표를 set //darw는 이놈은 그리는거 1자로
{
public:   //pure virtual type으로 선언하여, 나중의 Ipiece, Lpiece 등, 특정 Piece에 Polymorphism을 이용하여 포인터로 가리키게 함
	virtual int GetId() = 0;  //Piece의 Id를 get하여 piece의 Id와 blk의 id와 비교하여 정답을 비교할 계획
	virtual int GetType() = 0; //Piece의 type을 get함
	virtual void SetId(int Id) = 0;
	virtual int GetRotate() = 0; //piece의 회전 정보를 get함
	virtual void SetRotate(int Rotate) = 0;
	virtual int GetCx() = 0; //Piece의 x좌표를 get함
	virtual void SetCx(int Cx) = 0;
	virtual int GetCy() = 0; //Piece의 y좌표를 get함
	virtual void SetCy(int Cy) = 0;
	virtual void SetImage(int Cx, int Cy, int Rotate) = 0;
	virtual void Draw() = 0;
private:


};

class Ipiece : public Piece //Ipiece를 Piece로 상속받아 정의
{
public:
	Ipiece() { Type = ITYPE; Id = 0; Rotate = 0; } // Ipiece 초기화
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
	//=operator(A) {정의 하고 끝}

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