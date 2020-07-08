#pragma once
#include "Zwierze.h"
#define UCIECZKA 50
class Antylopa :
	public Zwierze
{
	int ruch;
public:
	Antylopa(Vector pos, Swiat* swiat);
	int kolizja(Organizm* other);//mozliwosc ucieczki kiedy cos ja zaatakuje atakujacy sie przesuwa
	void akcja();//podwojny ruch
	void makeChild(Vector pos);
 	void dajGlos();
	bool retreat(int pos);
	void move(int pos);
};

