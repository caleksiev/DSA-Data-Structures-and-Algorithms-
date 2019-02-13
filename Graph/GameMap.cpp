#include "GameMap.h"
const int MAX = 200;
/*
CTOR ->read from file the data for the map and create a graph
If the name of file is invalid or the started zone doesn't exist ->std::invalid_argument() exception is throwing
If some operation failed, during operation the file -> const char* exception is throwing
*/
GameMap::GameMap(const char * fileName, const char * from)
{
	if (!fileName || !from)
		throw std::invalid_argument("NULL ptr pass!\n");
	if (!checkFileExist(fileName))
		throw std::invalid_argument("The file can't opened.Maybe dosnt't exist!\n");
	readFromFile(fileName);
	graph::iterator it = gameMap.find(from);
	if (it == gameMap.end())
		throw std::invalid_argument("The started zone is invalid!\n");
	this->from = from;
	//unrichable[from] = false;//always
}

bool isLetter(char s)
{
	return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || s=='\n'|| s=='[';
}

void skipSpaces(std::fstream&f)
{
	char s = f.get();
	while (!isLetter(s))
		s = f.get();
	f.unget();
}
void GameMap::readFromFile(const char * fileName)
{
	char buff[MAX];
	std::fstream f(fileName, std::ios::in);
	if (!f)
		throw "File problem!\n";
	f.getline(buff, MAX);//skip the field "[zones]"
	readZones(f);
	f.get();//skip new line
	if (!f)
		throw "File problem!\n";
	readKeys(f);
	if (!f.eof())
		throw "File problem!\n";
}

void GameMap::readZones(std::fstream & f)
{
	char sector[MAX], key[MAX], adj[MAX];
	f.getline(sector, MAX, ' ');

	while (f && strcmp(sector, "[keys]"))
	{
		skipSpaces(f);
		f.getline(adj, MAX, ' ');
		addAdj(std::string(sector), std::string(adj));
		skipSpaces(f);
		if (f.get() != '\n')//the sector have a key
		{
			f.getline(key, MAX, ']');
			skipSpaces(f);
			f.get();//the new line
					//добави ключа за влизане
			setKey(std::string(adj), std::string(key));
		}
		f.getline(sector, MAX, ' ');
	}
}

void GameMap::readKeys(std::fstream & f)
{
	char type[MAX];
	char key[MAX];
	char where[MAX];
	while (!f.eof())
	{
		f.getline(type, MAX, ' ');
		f.getline(key, MAX, ' ');//skip the word 'key'
		skipSpaces(f);
		f.getline(where, MAX);
		char*newstr = strcat(type, " key");
		addKey(std::string(where), std::string(newstr));
	}

}

bool GameMap::checkFileExist(const char * fileName) const
{
	std::fstream f(fileName, std::ios::in);
	if (!f)
		return false;
	return true;
}
/*
Using the dot file syntax,write to the given stream information about the sector
*/
void GameMap::printSectorKey(std::ostream & os,const std::string&sector,  taken&takenKeys, bool unrichable)
{
	os << sector.data() << "[label=\"" << sector.data();//write the sector's name
	size_t  size = gameMap[sector].getKeysSize();
	//and the keys inside, if there are any
	for (size_t i = 0; i < size; ++i)
	{
		os << "\\l";
		std::string key = gameMap[sector].getKeys(i);
		os << key.data();//print the key
		takenKeys[key] = true;//and take it
	}
	if (unrichable)//make the sector red if is unrichable
		os << "\",color=red,style=filled,fillcolor=\"#ffefef";
	os << "\"];\n";
}
/*
Using the dot file syntax,write to the given stream information the adjacent vertex and 
the key for access to him,if there there are any
*/
void GameMap::printAdjKey(std::ostream & os, const std::string & from, const std::string & adj)
{

	os << from.data() << " -> " << adj.data();
	std::string key = gameMap[adj].getKey();
	if (key != "")
		os << " [label=\"" << key.data() << "\"]";
	os << ";\n";
	
}

void GameMap::addAdj(std::string&sector,std::string & who)
{
	gameMap[sector].addAdj(who);
	gameMap[who];//добавяме и съседа, в случай че не е все още
	visited[sector] = false;
	visited[who] = false;
}

void GameMap::addKey(std::string & sector, std::string & who)
{
	gameMap[sector].addKey(who);
}

void GameMap::setKey(std::string & sector, std::string & what)
{
	gameMap[sector].setKey(what);
}
/*
Graph traversal using dfs
*/
void GameMap::makeMap(std::ostream&os)
{
	taken takenKeys;//takenKeys[key] == true ,if the key is taken
	
	os << "digraph{\n";

	dfs(from, visited, takenKeys, os, false);

	//if there are unvisited sectors,they will be unrichable
	for (Used::iterator it = visited.begin(); it != visited.end(); ++it)
	{
		if (!it->second)
			dfs(it->first, visited, takenKeys, os, true);
	}
	os << "}";
}

void GameMap::dfs(const std::string& from,Used & visited, taken&takenKeys,std::ostream&os, bool unrichable)
{
	if (drawin.find(from) == drawin.end())//print the sector if still isn't
		printSectorKey(os, from, takenKeys, unrichable);//make the current scetor and take the key inside
	visited[from] = true;//marked as visisted
	drawin[from] = false;//marked as drawed
	size_t size = gameMap[from].getAdjSize();
	for (size_t i = 0; i <size; i++)
	{
		std::string adj = gameMap[from].getAdj(i);
		if (!drawfrom[from] || !drawto[adj])//if the rib from current sector to some adjacent isn't drawed
		{
			printAdjKey(os, from, adj);//make the rib
			//check that rib is already drawed
			drawfrom[from] = true;
			drawto[adj] = true;
		}
		//check whether  can move next
		std::string neededKey = gameMap[adj].getKey();
		if (neededKey == "" || takenKeys[neededKey])//there is no key or we already have the key ->move next
		{
			if (!visited[adj])
				dfs(adj, visited, takenKeys, os, unrichable);
		}
		else//can't move,make the sector unvisisted
			visited[from] = false;
	}
}
