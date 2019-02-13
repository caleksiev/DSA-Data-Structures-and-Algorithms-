#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<unordered_map>
#include<string.h>
#include<tuple>
#include<fstream>
#include<iostream>
#include<vector>
#include<cstring>
class MyTuple
{
public:
	MyTuple():neddedKey("")
	{}
public:
	void addKey(std::string& newKey)
	{
		keys.push_back(newKey);
	}
	void addAdj(std::string& newAdj)
	{
		adj.push_back(newAdj);
	}
	std::string getAdj(size_t index)
	{
		if (index >= adj.size())
			throw std::out_of_range("Invalid index!\n");
		return adj[index];
	}
	std::string getKeys(size_t index)
	{
		if (index >= keys.size())
			throw std::out_of_range("Invalid index!\n");
		return keys[index];
	}
	void setKey(std::string& newKey)
	{
		neddedKey = newKey;
	}
	size_t getKeysSize()const
	{
		return keys.size();
	}
	size_t getAdjSize()const
	{
		return adj.size();
	}
	std::string getKey()const
	{
		return neddedKey.data();
	}

	//the tuple for every vertex have 3 fields
private:
	using key = std::string;
	using vertex = std::string;
private:
	std::vector<key>keys;//list of all keys in the sector
	key neddedKey;//the needed key to enter in the sector ,"" if the sector  doesn't need a key to entering
	std::vector<vertex>adj;//list of adjacent sectors
};
