#include "chess.h"


//Satranç taþlarýnýn özelliklerinin txt dosyasý üzerinden alýnmasý
void getMans(std::vector<std::string> mans, Chess* chess)
{
	int tableInt = table::a;
	int i = 8;
	for (auto it : mans) {
		chessMan* man = nullptr;
		char element[3];
		strcpy(element, it.c_str());
		if (element[0] == 'k') {
			man = new castle();
			man->setType(Type::Castle);
		}

		else if (element[0] == 'a') {
			man = new horse();
			man->setType(Type::Horse);
		}

		else if (element[0] == 'f') {
			man = new elephant();
			man->setType(Type::Elephant);
		}

		else if (element[0] == 'v') {
			man = new queen();
			man->setType(Type::Queen);
		}

		else if (element[0] == 's') {
			man = new king();
			man->setType(Type::King);
		}

		else if (element[0] == 'p') {
			man = new pawn();
			man->setType(Type::Pawn);
		}
		if (element[1] == 's')
			man->setColor(chessColor::black);
		else if (element[1] == 'b')
			man->setColor(chessColor::white);
		if (man != nullptr)
			man->setPosition(tableInt, i);

		if (tableInt % 8 == 0) {
			i--;
			tableInt = 0;
		}
		if (man != nullptr)
			chess->addChessMan(man);
		tableInt++;
	}


}


chessMan::chessMan()
{
	this->position[0] = 0;
	this->position[1] = 0;
	this->color = chessColor::null;
	this->type = Type::Empty;
}

chessMan::~chessMan()
{
}

//Taþlarýn indekslerinin atanmasý
void chessMan::setPosition(int x, int y)
{
	this->position[0] = x;
	this->position[1] = y;
}

int* chessMan::getPosition()
{
	return this->position;
}

void chessMan::setColor(chessColor color)
{
	this->color = color;
}

chessColor chessMan::getColor()
{
	return this->color;
}

void chessMan::setType(Type type)
{
	this->type = type;
}
//Taþlarýn puanlarýnýn atanmasý
void chessMan::setPoint(int point)
{
	this->point = point;
}

int chessMan::getPoint()
{
	return this->point;
}

Type chessMan::getType()
{
	return this->type;
}

std::vector<chessMan*> chessMan::move(std::vector <chessMan*> manList)
{
	std::vector<chessMan*> x;
	return x;
}

std::vector<chessMan*> chessMan::moveForwardBackward(int mode, std::vector<chessMan*> manList)
{
	int* position = new int[2];
	int x, y = 0;
	position = this->getPosition();
	x = position[0];
	y = position[1];
	int k, l = 0;
	bool canMove = true;
	std::vector<chessMan*> blacklist;
	if (mode == 1) {
		//Forward
		for (int i = y + 1; i < 9; i++) {
			for (auto it : manList) {
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (i == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;

						}
						else {
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}
		//Backward
		for (int i = y - 1; i > 0; i--) {
			for (auto it : manList) {
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (i == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else {
							blacklist.push_back(it);
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}


	}
	else if (mode == 0) {
		//Forward, Backward
		for (auto it : manList) {
			l = it->getPosition()[1];
			k = it->getPosition()[0];
			if ((y+1 == l && x == k)|| (y - 1 == l && x == k)) {
				if (it->color == this->color)
					break;
				else
				{
					blacklist.push_back(it);
				
				}
			}
		}
	


	}
	return blacklist;
}

std::vector<chessMan*> chessMan::moveLeftRight(int mode, std::vector<chessMan*> manList)
{
	int* position = new int[2];
	int x, y = 0;
	position = this->getPosition();
	x = position[0];
	y = position[1];
	int k, l = 0;
	bool canMove = true;
	std::vector<chessMan*> blacklist;
	if (mode == 1) {
		for (int i = x + 1; i < 9; i++) {
			for (auto it : manList) {
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (y == l && i == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;

						}
						else {
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}
		for (int i = x - 1; i > 0; i--) {
			for (auto it : manList) {
				l = it->getPosition()[1]; // iterator's y index
				k = it->getPosition()[0]; //iterator's x index
				if (y == l && i == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else {
							blacklist.push_back(it);
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}
	}
	else if (mode == 0) {
		//Right, Left
		for (auto it : manList) {
			l = it->getPosition()[1];
			k = it->getPosition()[0];
			if ((x + 1 == k && y == l )|| (x - 1 == k && y == l)) {
				if (it->color == this->color)
					break;
				else {
					blacklist.push_back(it);
				}
			}
		}
	}

	return blacklist;
}

std::vector<chessMan*> chessMan::moveCross(int mode, std::vector<chessMan*> manList)
{
	int* position = new int[2];
	int x, y = 0;
	position = this->getPosition();
	x = position[0];
	y = position[1];
	int k, l = 0;
	bool canMove = true;
	std::vector<chessMan*> blacklist;
	if (mode == 1) {
		//Right Up
		while (true) {
			x++;
			y++;
			if (x > 8 || y > 8)
				break;
			for (auto it : manList) {
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (y == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else {
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}
		x = position[0];
		y = position[1];
		//Left Down
		while (true) {
			x--;
			y--;
			if (x < 1 || y < 1)
				break;
			for (auto it : manList) {
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (y == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else 
						{
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}
		x = position[0];
		y = position[1];
		while (true) {
			x--;
			y++;
			if (x < 1 || y > 8)
				break;
			for (auto it : manList) {
				//Left Up
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (y == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else {
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}

		}
		x = position[0];
		y = position[1];
		while (true) {
			x++;
			y--;
			if (x > 8 || y > 8)
				break;
			for (auto it : manList) {
				//Right down
				l = it->getPosition()[1];
				k = it->getPosition()[0];
				if (y == l && x == k) {
					if (it->type != Type::Empty) {
						if (it->color == this->color) {
							canMove = false;
							break;
						}
						else {
							blacklist.push_back(it);
							canMove = false;
							break;
						}
					}
				}
			}
			if (canMove == false) {
				canMove = true;
				break;
			}
		}

	}
	else if (mode == 0) {
	//Beyaz piyonlar için özel fonksiyon
		if ((this->getType() == Type::Pawn && this->color == chessColor::white) || this->getType() != Type::Pawn) {
			//Right up
			for (auto it : manList) {
				k = it->getPosition()[0];
				l = it->getPosition()[1];
				if ((x + 1 == k && y + 1 == l)|| (x - 1 == k && y + 1 == l)) {
					if (it->color == this->color)
						break;
					else {
						blacklist.push_back(it);
					
					}
				}
			}
		}
		//Siyah piyonlar için özel fonksiyon
		if ((this->getType() == Type::Pawn && this->color == chessColor::black) || this->getType() != Type::Pawn) {
			for (auto it : manList) {
				//Right down
				k = it->getPosition()[0];
				l = it->getPosition()[1];
				if ((x + 1 == k && y - 1 == l) || (x - 1 == k && y - 1 == l)){
					if (it->color == this->color)
						break;
					else {
						blacklist.push_back(it);
					
					}
				}
			}
		}

	}
	return blacklist;
}

Chess::Chess()
{

}

Chess::~Chess()
{
	for (auto it : this->manList)
		delete it;
	this->manList.clear();
	this->blacklist.clear();
}

int Chess::getPoint()
{
	std::vector<chessMan*> x;
	float totWh=0, totBl = 0; //Toplam beyaz ve siyah puan
	float  DanWh=0, DanBl = 0; // Tehlikede olan beyaz ve siyah puan
	float ResWh=0, ResBl = 0; // Tüm iþlemler sonucu nihai puanlar
	for (auto it : manList) {
		if (it->getType() != Type::Empty)
			x = it->move(this->manList);
		if (x.size() != 0)
			this->blacklist.insert(blacklist.end(), x.begin(), x.end());
		x.clear();

	}
	//Blacklistte ayný olan elementlerin silinmesi
	std::sort(this->blacklist.begin(), this->blacklist.end());
	auto last = std::unique(this->blacklist.begin(), this->blacklist.end());
	this->blacklist.erase(last, this->blacklist.end());
	for (auto it : this->manList) {
		if (it->getColor() == chessColor::white)
			totWh += it->getPoint();
		else
			totBl += it->getPoint();
	}
	for(auto it : blacklist)
		if (it->getColor() == chessColor::white)
			DanWh += it->getPoint();
		else
			DanBl += it->getPoint();
		
	ResWh = totWh - (DanWh / 2);
	ResBl = totBl - (DanBl / 2);
	std::cout << "Siyah:" << ResBl << "\t";
	std::cout <<"Beyaz:" << ResWh << std::endl;
	

	return 0;
}

void Chess::addChessMan(chessMan* man)
{
	this->manList.push_back(man);
}

pawn::pawn()
{
	this->setPoint(1);
}

pawn::~pawn()
{
}
castle::castle()
{
	this->setPoint(5);
}

castle::~castle()
{
}
horse::horse()
{
	this->setPoint(3);
}

horse::~horse()
{
}
elephant::elephant()
{
	this->setPoint(3);
}

elephant::~elephant()
{
}
queen::queen()
{
	this->setPoint(9);
}

queen::~queen()
{
}
king::king()
{
	this->setPoint(100);
}

king::~king()
{
}

std::vector<chessMan*> king::move(std::vector <chessMan*> manList)
{
	auto k = this->moveForwardBackward(0, manList);
	auto l = this->moveCross(0, manList);
	if (l.size() != 0)
		k.insert(k.end(), l.begin(), l.end());
	auto j = this->moveLeftRight(0, manList);
	if (j.size() != 0)
		k.insert(k.end(), j.begin(), j.end());

	return k;

}

std::vector<chessMan*> queen::move(std::vector <chessMan*> manList)
{

	auto k = this->moveForwardBackward(1, manList);
	auto l = this->moveCross(1, manList);
	if (l.size() != 0)
		k.insert(k.end(), l.begin(), l.end());
	auto j = this->moveLeftRight(1, manList);
	if (j.size() != 0)
		k.insert(k.end(), j.begin(), j.end());

	return k;

}
std::vector<chessMan*> elephant::move(std::vector <chessMan*> manList)
{
	auto k = this->moveCross(1, manList);
	return k;

}
std::vector<chessMan*> horse::move(std::vector <chessMan*> manList)
{
	int* position = new int[2];
	int x, y = 0;
	position = this->getPosition();
	x = position[0];
	y = position[1];
	int k, l = 0;
	std::vector<chessMan*> blacklist;
	//Allways
	for (auto it : manList) {
		k = it->getPosition()[0];
		l = it->getPosition()[1];
		if ((x + 2 == k && y + 1 == l) || (x + 1 == k && y + 2 == l) || (x - 2 == k && y + 1 == l) ||
			(x - 1 == k && y + 2 == l) || (x - 2 == k && y - 1 == l) || (x - 1 == k && y - 2 == l) ||
			(x + 2 == k && y - 1 == l) || (x + 1 == k && y - 2 == l)) {
			if (it->getColor() == this->getColor())
				continue;
			else {
				blacklist.push_back(it);
			}
		}
	}
	return blacklist;
}




std::vector<chessMan*> castle::move(std::vector <chessMan*> manList)
{
	auto k = this->moveForwardBackward(1, manList);
	auto l = this->moveLeftRight(1, manList);
	if (l.size() != 0)
		k.insert(k.end(), l.begin(), l.end());
	return k;

}
std::vector<chessMan*> pawn::move(std::vector <chessMan*> manList)
{
	auto k = this->moveCross(0, manList);
	return k;

}