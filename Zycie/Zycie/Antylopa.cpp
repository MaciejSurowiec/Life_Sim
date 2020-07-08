#include "Antylopa.h"

Antylopa::Antylopa(Vector pos, Swiat* sw)
{
	swiat = sw;
	pozycja = pos;
	inicjatywa = 4;
	ruch = 0;
	sila = 4;
	avatar = '^';
	toyoung = true;
	rozmn = true;
	swiat->setMapElement(pozycja, this);
	swiat->pushToWorld(this);
	std::cout << "Narodziny ";
	dajGlos();
	std::cout << std::endl;
}

void Antylopa::makeChild(Vector pos)
{
	Antylopa* org;
	org = new Antylopa(pos, swiat);
}

void Antylopa::dajGlos()
{
	std::cout << "Antylopa";
}

void Antylopa::akcja()
{
	if (toyoung) toyoung = false;
	else
	{
		ruch = 0;
		int r = 0;
		r = rand() % DIRECTIONS;
		move(r);
	}
	rozmn = false;
}


int Antylopa::kolizja(Organizm * temp)
{
	if (temp->checkGatunek(avatar))
	{
		if (!toyoung && !temp->mature())
		{
			if (!rozmn && !temp->getRozmn())
			{
				rozmn = true;
				temp->turnRozmn();
				rozmnazanie();
			}
		}
		return NARODZINY;
	}
	else
	{
		if (sila > temp->getSila())
		{
			dajGlos();
			std::cout << " zabija ";
			temp->dajGlos();
			std::cout << std::endl;
			swiat->checkCzlowiek(temp);
			return SMIERC;
		}
		else
		{
			int r = rand() % PROCENTY;
			if (r > UCIECZKA)
			{
				temp->dajGlos();
				std::cout << " zabija ";
				dajGlos();
				std::cout << std::endl;
				swiat->setMapElement(pozycja, nullptr);
				delete this;
				return ZWYCIESTWO;
			}
			else
			{
				if (retreat(rand() % DIRECTIONS))
				{
					dajGlos();
					std::cout << " ucieka ";
					temp->dajGlos();
					std::cout << std::endl;
					return NARODZINY;
				}
				else
				{
					temp->dajGlos();
					std::cout << "zabija ";
					dajGlos();
					swiat->setMapElement(pozycja, nullptr);
					delete this;
					return ZWYCIESTWO;
				}
			}
		}
	}
}

bool Antylopa::retreat(int pos)
{
	if (pos < DIRECTIONS * 2)
	{
		if (!swiat->checkPosition(pozycja + Direction(pos)))
		{
			retreat(pos + 1);
		}
		else
		{
			if (!swiat->freePosition(pozycja + Direction(pos)))
			{
				retreat(pos + 1);
			}
			else
			{
				swiat->setMapElement(pozycja, nullptr);
				pozycja += Direction(pos);
				swiat->setMapElement(pozycja, this);
				return true;
			}
		}
	}
	else return false;
}

void Antylopa::move(int pos)
{
	if (pos < DIRECTIONS * 2)
	{
		if (!swiat->checkPosition(pozycja + Direction(pos))) move(pos + 1);
		else
		{
			if (!swiat->freePosition(pozycja + Direction(pos)))
			{
				Organizm* oponent = swiat->getMapElement(pozycja + Direction(pos));
				swiat->setMapElement(pozycja, nullptr);
				int temp = oponent->kolizja(this);//robie kolizje w obiekcie zderzonym zeby sprawdzic czy to nie zolf czy cos
				if (temp > 0)
				{
					if (temp == SMIERC) delete this;
					else
					{
						if (temp == ZWYCIESTWO)
						{
							pozycja += Direction(pos);
							swiat->setMapElement(pozycja, this);
							if (ruch < 2)
							{
								ruch++;
								int r = rand() % DIRECTIONS;
								move(r);
							}
						}
					}
				}
				else
				{
					swiat->setMapElement(pozycja, this);
					if (ruch < 2)
					{
						ruch++;
						int r = rand() % DIRECTIONS;
						move(r);
					}
				}
			}
			else
			{
				swiat->setMapElement(pozycja, nullptr);
				pozycja += Direction(pos);
				swiat->setMapElement(pozycja, this);
				if (ruch < 2)
				{
					ruch++;
					int r = rand() % DIRECTIONS;
					move(r);
				}
			}
		}
	}
}