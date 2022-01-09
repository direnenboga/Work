#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

enum chessColor {

	white = 0,
	black = 1,
	null = 2

};

//X ekseni için eþdeðer tablosu
enum table {

	a = 1,
	b = 2,
	c = 3,
	d = 4,
	e = 5,
	f = 6,
	g = 7,
	h = 8
};

enum Type {
	Empty = 0,
	Castle = 1,
	Horse = 2,
	Elephant = 3,
	Queen = 4,
	King = 5,
	Pawn = 6


};




class chessMan {

	int position[2];
	chessColor color;
	Type type;
	int point = 0;
public:
	chessMan();
	~chessMan();
	void setPosition(int x, int y);
	int* getPosition();
	void setColor(chessColor color);
	chessColor getColor();
	void setType(Type type);
	void setPoint(int point);
	int getPoint();
	Type getType();
	virtual std::vector<chessMan*> move(std::vector <chessMan*> manList);
	//Mode == 0 , One step , Mode == 1 , infinity step
	std::vector<chessMan*> moveForwardBackward(int mode, std::vector <chessMan*> manList);
	std::vector<chessMan*> moveLeftRight( int mode, std::vector <chessMan*> manList);
	std::vector<chessMan*> moveCross( int mode, std::vector <chessMan*> manList);
};


class Chess {
	std::vector <chessMan*> manList;
	std::vector <chessMan*> blacklist; // Blacklist tehlikede olan taþlarýn listesi
public:
	Chess();
	~Chess();
	int getPoint();
	void addChessMan(chessMan* man);
	
};


// x+1 or y+1
class pawn : public chessMan {
public:
	pawn();
	~pawn();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;



};

// x++ or y++
class castle : public chessMan {
public:
	castle();
	~castle();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;


};

// y+=2 and x+1 or x+=2 and y+1
class horse : public chessMan {
public:
	horse();
	~horse();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;
};

// x+1 and y+1
class elephant : public chessMan {
public:
	elephant();
	~elephant();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;
};

// all of them
class queen : public chessMan {
public:
	queen();
	~queen();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;
};

// +1 everywhere
class king : public chessMan {
public:
	king();
	~king();
	std::vector<chessMan*> move(std::vector <chessMan*> manList) override;
};



void getMans(std::vector<std::string> mans,Chess* chess);



