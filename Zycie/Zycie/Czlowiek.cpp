#include "Czlowiek.h"

Czlowiek::Czlowiek(Vector pos, Swiat* sw)
{
	swiat = sw;
	pozycja = pos;
	inicjatywa =4;
	sila = 5;
	avatar = 'C';
	toyoung = true;
	moc = 0;
	ruch = 0;
	swiat->setMapElement(pozycja, this);
	swiat->pushToWorld(this);
	life = true;
	std::cout << "Narodziny ";
	dajGlos();
	std::cout << std::endl;
}

Czlowiek::~Czlowiek()
{
	std::cout << "Czlowiek umiera"<<std::endl<< "KONIEC GRY";
	swiat->deleteFromList(this);
}

void Czlowiek::akcja()//moc rosnie w kazdej turze a gdy osiagnie 5 przechodzi na -5 i wtedy znowu rosnie az bedzie 0 i czeka na przycisk
{
	move(ruch);

	if (moc > 0)
	{
		std::cout << "moc bedzie jeszcze trwac " << POWER_LENGTH-(moc-1) << " tur" << std::endl;
		zabijWokolo();
	}

	if (moc !=0) moc++;

	if (moc == POWER_LENGTH+1) moc = -1*POWER_LENGTH;
}

void Czlowiek::getMove()
{
	bool loop = true;
	while (loop)
	{
		ruch = -1;
		loop = false;
		char c = _getch();

		switch (c)
		{
		case SPACE:	
			if (checkPower()) {
				moc = 1;
				std::cout << "Moc aktywowana bedzie trwac: " << POWER_LENGTH - (moc - 1) << std::endl;
			}
			else {
				if (moc < 0) std::cout << "Mocy bedzie mozna uzyc za " << moc * -1 << "tur" << std::endl;
				else std::cout << "Mocy bedzie trwac jeszcze " << POWER_LENGTH-(moc-1) << "tur" << std::endl;
				loop = true;
			}
			break;
		case KEY_UP:	ruch = UP;
			break;
		case KEY_DOWN:	ruch = DOWN;
			break;
		case KEY_LEFT:	ruch = LEFT;
			break;
		case KEY_RIGHT:	ruch = RIGHT;
			break;
		case 'q': 
			life = false;
			loop = false;
			break;
		default: loop = true;
			break;
		}

		if (life)
		{
			if (ruch < 0)loop = true;

			if (!swiat->checkPosition(pozycja + Direction(ruch)) && !loop) loop = true;
		}
	}
}

void Czlowiek::dajGlos()
{
	std::cout << "Czlowiek";
}

bool Czlowiek::checkPower()
{
	if (moc == 0) return true;
	else return false;
}

void Czlowiek::zabijWokolo()
{
	for (int i = 0; i < DIRECTIONS; i++)
	{
		if (swiat->checkPosition(pozycja + Direction(i)))
		{
			if (!swiat->freePosition(pozycja + Direction(i)))
			{
				Organizm* temp = swiat->getMapElement(pozycja + Direction(i));
				
				swiat->setMapElement(pozycja + Direction(i), nullptr);
				std::cout << "moc  czlowieka zabila: ";
				temp->dajGlos();
				std::cout << std::endl;
				delete temp;
			}
		}
	}
}


bool Czlowiek::getLife()
{
	return life;
}

void Czlowiek::makeChild(Vector pos) { ; }