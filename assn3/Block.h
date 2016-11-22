#pragma once
#include<iostream>

class Block
{
public:
	int GetAnswerId() { return Id; }
	int GetBlockMarked() {return Mark;}
	void SetAnswerId(int Id) { this->Id = Id; }
	void SetBlockMarked(int Mark) { this->Mark = Mark; }
	Block() { Id = 0; Mark = 0; }
	~Block() {}

private:
	int Id;
	int Mark;
};
