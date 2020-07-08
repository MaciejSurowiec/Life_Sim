#include "BarszczSosnowskiego.h"
BarszczSosnowskiego::BarszczSosnowskiego(Vector vec, Swiat* sw)
{
	swiat = sw;
	pozycja = vec;
	inicjatywa = 0;
	sila = 0;
	avatar = '!';
	toyoung = true;
	swiat->setMapElement(pozycja, this);
	swiat->pushToWorld(this);

	std::cout << "Narodziny ";
	dajGlos();
	std::cout << std::endl;
}

void BarszczSosnowskiego::dajGlos()
{
	std::cout << "Barszcz Sosnowskiego";
}

void BarszczSosnowskiego::makeChild(Vector pos)
{
	BarszczSosnowskiego* org;
	org = new BarszczSosnowskiego(pos, swiat);
}

int BarszczSosnowskiego::kolizja(Organizm* temp)
{
	temp->dajGlos();
	std::cout << " wchodzi na ";
	dajGlos();
	std::cout << ": ";

	temp->dajGlos();
	std::cout << " niszczy ";
	dajGlos();
	std::cout << " : ";
	dajGlos();
	std::cout<< " zatruwa ";
	temp->dajGlos();
	std::cout << std::endl;
	swiat->checkCzlowiek(temp);
	swiat->setMapElement(pozycja, nullptr);
	delete this;
	return SMIERC;
}

void BarszczSosnowskiego::akcja()
{
	if (toyoung)toyoung = false;
	else
	{
		int r = rand() % PROCENTY;

		if (r < ZAPYLENIE)
		{
			r = rand() % DIRECTIONS;
			zapylenie(r);
		}
	}

	zabijWokolo();
}

void BarszczSosnowskiego::zabijWokolo()
{
	for (int i = 0; i < DIRECTIONS; i++)
	{
		if (swiat->checkPosition(pozycja+Direction(i)))
		{
			if (!swiat->freePosition(pozycja + Direction(i)))
			{
				Organizm* temp = swiat->getMapElement(pozycja+Direction(i));
				if (temp->getInic() > 0)
				{
					swiat->setMapElement(pozycja + Direction(i), nullptr);
					dajGlos();
					swiat->checkCzlowiek(temp);
					std::cout << " zabil na odleglosc: ";
					temp->dajGlos();
					std::cout << std::endl;
					delete temp;
				}
			}
		}
	}
}
