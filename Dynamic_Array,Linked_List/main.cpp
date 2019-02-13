#include"Menu.h"

int main()
{
	std::cout << "1)append NAME UNI INDEX\n"
		<< "2)removeLast INDEX\n"
		<< "3)removeFirst INDEX\n"
		<< "4)remove NAME INDEX\n"
		<< "5)merge INDEX INDEX\n"
		<< "6)print\n"
		<< "7)quit\n";
	while (true)
	{
		char command[MAX_LEN];//ånter a command
		std::cout << "$:";
		std::cin >> command;
		try
		{
			//try to execute it
			Menu::getInstance().runCommand(command, std::cout, std::cin);
		}
		//if there is a problem thet can be solved,report it to the user
		catch (const std::invalid_argument&ex)
		{
			std::cout << ex.what();
		}
		catch (const std::out_of_range&ex)
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
			if (!strcmp(ex, QUIT))
				break;
			else
				throw;
		}
		//if there is somethig left on the stream->ingore it
		std::cin.clear();
		std::cin.unget();
		std::cin.ignore(1000, '\n');
		std::cin.sync();
	}
	return 0;
}
