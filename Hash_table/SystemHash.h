#ifndef SHASH_HEADER_INCLUDED
#define HASH_HEADER_INCLUDED
#include"RoundDance.h"
#include<vector>
#include<fstream>
class SystemHash
{
	struct Box
	{
		RoundDance::Box *ptrTo = nullptr;
	};
public:
	SystemHash(const char*fileName);
public:
	void grab(const std::string&name, const std::string&);
	void release(const std::string&name, const std::string&);
	void info(const std::string&name, std::ostream&os)const;
	void print(std::ostream&os)const;
	void swap(const std::string&name1, const std::string&name2);
	void add(const std::string&newPerson, const std::string&name1, const std::string&name2);
	void remove(const std::string&name);
	size_t getSize()const { return size; }
private:
	static size_t hashFunction(const std::string& str, const size_t size);
	void insert(const std::string& str);
	int  get(const std::string&name)const;
	void erase(size_t  index);
private:
	void rehash();
	bool readFromFile(const char*filename);
	size_t getIndex(const std::string&name)const;
private:
	using HashTable = std::vector<Box>;
	HashTable table;//array of pointers to every person in the dance
	RoundDance dance;//the dance,represent with circle list
	size_t size;//current people in the dance
};
#endif
