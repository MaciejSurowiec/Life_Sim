#pragma once
#include "Zwierze.h"
#include "conio.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define POWER_LENGTH 5

class Czlowiek :
	public Zwierze
{
	int ruch;
	int moc;
	bool life;
public:
	Czlowiek(Vector pos, Swiat* swiat);
	void akcja();//wrzucenie move do funkcji 
	void getMove();//pobranie ruchu 
	void dajGlos();
	bool checkPower();
	void zabijWokolo();
	bool getLife();
	void makeChild(Vector pos);
	~Czlowiek();
};

