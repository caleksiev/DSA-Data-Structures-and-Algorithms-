#include"Menu.h"
bool checkFileisValid(const char*filename)
{
	std::fstream f;
	f.open(filename, std::ios::in);
	if (!f)
		return false;
	return true;
}

void skipRest(std::istream&in)
{
	in.clear();
	in.unget();
	in.ignore(1000, '\n');
	in.sync();
	in.clear();

}
int main()
{
	std::cout << "Enter a filePath:";
	char buff[500];
	std::cin.getline(buff, 500);
	while (!checkFileisValid(buff))
	{
		skipRest(std::cin);
		std::cout << "Enter a CORRECT filePath:";
		std::cin.getline(buff, 500);
	}
	skipRest(std::cin);
	std::cout << "1)RELEASE who,[left|right|both]\n"
		<< "2)GRAB who,[left|right|both]\n"
		<< "3)PRINT\n"
		<< "4)INFO who\n"
		<< "5)ADD who,labelLeft,labelRight\n"
		<< "6)REMOVE who\n"
		<< "7)SWAP who1,who2\n";
	try
	{
		//"C:/Users/PC/Desktop/SDP/Homework 2/Project1/Project1/test.txt"
		Menu menu(buff);
		while (true)
		{
			char command[100];
			std::cout << "Enter a command:";
			std::cin >> command;
			try
			{
				menu.runCommand(command, std::cout, std::cin);
			}
			catch (const std::invalid_argument&ex)
			{
				std::cout << ex.what();
			}
			catch (const std::bad_alloc&ex)
			{
				std::cout << ex.what();
				break;
			}
			catch (const char*ex)
			{
				if (!strcmp(ex, "EXIT"))
				{
					std::cout << "..and the music stops!\n";
					break;
				}
				else
					throw;
			}
			//if there is somethig left on the stream->ingore it
			skipRest(std::cin);
		}
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}
	return 0;
}