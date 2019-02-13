#include"GameMap.h"
int main()
{
	/*
	Тъй като акецентът на домашното не е върху,четене от файл,съм променил леко входния файл
	от този в условието по следния начин:
	[zones]
	zone1 - adj1 - ['type' key] or -
	zone2 - adj2 - ['type' key] or -
	.....
	zoneN - adjn - ['type' key] or -
	[keys] 'space'
	'type' key1 - where
	'type' key2 - where
	.....
	'type' keyN - where
	=[zones]
	На всеки ред се очакват три неща разделени с символът '-',ограден с whitespace:
	1)Името на зоната
	2)Името на нейния съсед
	*Имената не може да бъдат с whitespace
	3)Ключа необходим за влизане в зоната,ограден в '[]'
	*Ако такъв няма се отбелязва ';'
	=[keys]
	На всеки ред се очакват две неща разделени със '-',ограден с whitespace
	1)Името на ключа
	2)В коя зона се намира(без whitespace)
	Ако файлът не е коректен програмата няма да работи правилно :)
	*/
	while (true)
	{
		//C:\\Users\\PC\\Desktop\\SDP/Homework 3\\Project1\\Project1\\test.txt
		char filePath[1024];
		char start[100];
		try
		{
			std::cout << "Enter a filePath:";
			std::cin.getline(filePath, 1024);
			std::cout << "Enter a start zone:";
			std::cin >> start;
			GameMap m(filePath, start);
			std::fstream f("text.dot", std::ios::out);
			m.makeMap(f);
			std::cout << "The file was generated!\n";
			break;

		}
		catch (const std::invalid_argument& ex)
		{
			std::cout << ex.what();
			std::cin.get();
		}
		catch (const char*ex)
		{
			std::cout << ex;
			break;
		}
		catch (...)
		{
			std::cout << "Unkown problem!\n";
			break;
		}
	}
	return 0;
}