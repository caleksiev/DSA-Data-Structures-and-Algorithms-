#include "Menu.h"


Menu::Menu(const char*fileName) :hash(fileName) {}



void Menu::runCommand(const char*com, std::ostream&os, std::istream&in)
{
	if (!strcmp(com, "RELEASE"))
	{
		releaseCommand(in, os);
	}
	else if (!strcmp(com, "GRAB"))
	{
		grabCommand(in, os);
	}
	else if (!strcmp(com, "PRINT"))
	{
		printCommand(os);
	}
	else if (!strcmp(com, "INFO"))
	{
		infoCommand(in, os);
	}
	else if (!strcmp(com, "ADD"))
	{
		addCommand(in, os);
	}
	else if (!strcmp(com, "REMOVE"))
	{
		removeCommand(in, os);
	}
	else if (!strcmp(com, "SWAP"))
	{
		swapCommand(in, os);
	}
	else if (!strcmp(com, "EXIT"))
	{
		throw "EXIT";
	}
	else
		throw std::invalid_argument("UKNOWN");

}

void Menu::releaseCommand(std::istream & in, std::ostream & os)
{
	char name[MAX_NAME];
	char what[MAX_WHAT];

	skipSpaces(in);
	in.getline(name, MAX_NAME, ',');
	skipSpaces(in);
	in.getline(what, MAX_NAME);

	hash.release(name, what);
	os << "Successfully released!\n";
}

void Menu::grabCommand(std::istream & in, std::ostream & os)
{
	char name[MAX_NAME];
	char what[MAX_WHAT];

	skipSpaces(in);
	in.getline(name, MAX_NAME, ',');
	skipSpaces(in);
	in.getline(what, MAX_NAME);

	hash.grab(name, what);
	os << "Successfully grabed!\n";
}

void Menu::infoCommand(std::istream & in,std::ostream & os) const
{
	char name[MAX_NAME];
	skipSpaces(in);
	in.getline(name, MAX_NAME);
	hash.info(name, os);
}

void Menu::printCommand(std::ostream & os) const
{
	hash.print(os);
}

void Menu::addCommand(std::istream & in,std::ostream & os)
{
	char newPerson[MAX_NAME];
	char name1[MAX_NAME];
	char name2[MAX_NAME];

	skipSpaces(in);
	in.getline(newPerson, MAX_NAME, ',');
	skipSpaces(in);
	in.getline(name1, MAX_NAME, ',');
	skipSpaces(in);
	in.getline(name2, MAX_NAME);


	hash.add(newPerson, name1, name2);

	os << "Successfull added!\n";
}

void Menu::removeCommand(std::istream & in, std::ostream & os)
{
	char name[MAX_NAME];
	skipSpaces(in);
	in.getline(name, MAX_NAME);
	hash.remove(name);

	if (hash.getSize() == 2)
		throw "EXIT";
	os << "Free at last!\n";
}

void Menu::swapCommand(std::istream & in, std::ostream & os)
{
	char name1[MAX_NAME];
	char name2[MAX_NAME];

	skipSpaces(in);
	in.getline(name1, MAX_NAME, ',');
	skipSpaces(in);
	in.getline(name2, MAX_NAME);

	hash.swap(name1, name2);

	os << "Succsessfully swaped!\n";
}


void Menu::skipSpaces(std::istream & in) const
{
	char s = in.get();
	while (s == ' ')
		s = in.get();
	in.unget();
}

