#include"GameMap.h"
int main()
{
	/*
	��� ���� ��������� �� ��������� �� � �����,������ �� ����,��� �������� ���� ������� ����
	�� ���� � ��������� �� ������� �����:
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
	�� ����� ��� �� ������� ��� ���� ��������� � �������� '-',������� � whitespace:
	1)����� �� ������
	2)����� �� ������ �����
	*������� �� ���� �� ����� � whitespace
	3)����� ��������� �� ������� � ������,������� � '[]'
	*��� ����� ���� �� ��������� ';'
	=[keys]
	�� ����� ��� �� ������� ��� ���� ��������� ��� '-',������� � whitespace
	1)����� �� �����
	2)� ��� ���� �� ������(��� whitespace)
	��� ������ �� � �������� ���������� ���� �� ������ �������� :)
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