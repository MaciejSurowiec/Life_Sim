#pragma once
#include "Roslina.h"
class BarszczSosnowskiego :
	public Roslina
{
public:
	BarszczSosnowskiego(Vector vec, Swiat* sw);
	void dajGlos();
	void makeChild(Vector vec);
	int kolizja(Organizm* temp);
	void akcja();
	void zabijWokolo();
};

