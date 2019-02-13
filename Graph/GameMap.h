#pragma once
#include"MyTuple.h"
class GameMap
{
private:
	using vertex = std::string;
	using key = std::string;
	using graph = std::unordered_map<vertex, MyTuple >;
	using Used = std::unordered_map<vertex, bool>;
	using drawIn = std::unordered_map<vertex, bool>;
	using taken = std::unordered_map<key, bool>;
	using drawFrom = std::unordered_map<vertex, bool>;
	using drawTo = std::unordered_map<vertex, bool>;
public:
	GameMap(const char*fileName, const char*from);
	void makeMap(std::ostream&os);
private:
	void readFromFile(const char*fileName);
	void readZones(std::fstream&f);
	void readKeys(std::fstream&f);
	bool checkFileExist(const char*fileName)const;
private:
	void printSectorKey(std::ostream&os, const std::string&from,  taken&takenKeys,bool unrichable);
	void printAdjKey(std::ostream&os, const std::string & from,const std::string&adj);
private:
	void addAdj(std::string&sector,std::string&who);
	void addKey(std::string&sector, std::string&who);
	void setKey(std::string&sector, std::string&what);
private:
	void dfs(const std::string& from,Used&visisted,  taken&,std::ostream&os,bool unrichable);
private:
	graph gameMap;//the graph
	vertex from;//initial sector
	Used visited;//list of visited sectors,in the beginning all sectors are false
private:
	drawIn drawin;//drawin[sectror]== true, if already have a vertex of this sector
	drawFrom drawfrom;//drawfrom[sector]==true, if already have a rip from this sector
	drawTo drawto;//drawto[sector]==true if, already have a rip to this sector
};
