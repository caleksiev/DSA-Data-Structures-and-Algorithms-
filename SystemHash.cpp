#include "SystemHash.h"
const size_t MAX = 31;
/*
CTOR -> read from file the data,then store it in the dance and make connection with the hash
If error occurs during opration the file->exception char* is throwing
*/
SystemHash::SystemHash(const char * fileName) :table(2),size(0)
{
	if (!readFromFile(fileName))
		throw "File error!\n";
}
/*
Search the person with "name" through the hash in the dance,and grab its "what"(left,right,both)neighbor
If the data is invalid std::invalid_argument is throwing
*/
void SystemHash::grab(const std::string & name, const std::string& what)
{
	size_t index = getIndex(name);
	if (what == "left")
		dance.grab(table[index].ptrTo, LEFT);
	else if (what == "right")
		dance.grab(table[index].ptrTo, RIGHT);
	else if (what == "both")
		dance.grab(table[index].ptrTo, BOTH);
	else
		throw std::invalid_argument("Unvalid neighbor/neighbors - left,right or both!\n");
}
/*
Search the person with "name" through the hash in the dance,and release its "what"(left,right,both)neighbor
If the data is invalid std::invalid_argument is throwing
*/
void SystemHash::release(const std::string & name, const std::string& what)
{
	size_t index = getIndex(name);
	if (what == "left")
		dance.release(table[index].ptrTo, LEFT);
	else if (what == "right")
		dance.release(table[index].ptrTo, RIGHT);
	else if (what == "both")
		dance.release(table[index].ptrTo, BOTH);
	else
		throw std::invalid_argument("Unvalid neighbor/neighbors - left,right or both!\n");
}
/*
Print information about the hold status of person with "name and his neighbors on some stream
If the stream isn't ok the method doesn't nothing
If the name doesn't exist std::invalid_argument is throwing
*/
void SystemHash::info(const std::string & name,std::ostream&os) const
{
	if (!os)
		return;
	size_t index = getIndex(name);
	dance.info(table[index].ptrTo, os);
}
/*
Print information about the names in all people in the dance through the hash on some stream
If the stream isn't ok the method doesn't nothing
*/
void SystemHash::print(std::ostream & os) const
{
	if (!os)
		return;
	dance.print(os);
}
/*
Try to move the positions of people -"name1" and "name2" in the dance through the hash
If the swap is successfull then swap the pointers in the hash,otherwise std::invalid_argument is throwing  
*/
void SystemHash::swap(const std::string & name1, const std::string & name2)
{
	size_t index1 = getIndex(name1);
	size_t index2 = getIndex(name2);
	if (dance.swap(table[index1].ptrTo, table[index2].ptrTo))
		std::swap(table[index1].ptrTo, table[index2].ptrTo);
	else
		throw std::invalid_argument("The persons can't be swaped!\n");
}
/*
Try to add a "newPerson" to the dance through the hash between "name1" and "name2"
Fisrt search for a free postition where should be added the "newPerson"
If find a person with the same name as "newPerson" std::invalid_argument is throwing
If the add is succsessfull connect the hash with the "newPerson"
Othewise std::invalid_argument is throwing
*/
void SystemHash::add(const std::string & newPerson, const std::string & name1, const std::string & name2)
{
	size_t index1 = getIndex(name1);
	size_t index2 = getIndex(name2);
	
	size_t index = hashFunction(newPerson, table.size());
	if (size * 2 >= table.size())//check is resize is nedded
	{
		rehash();
		index = hashFunction(newPerson, table.size());
	}
	size_t tryies = table.size();
	while (--tryies && table[index].ptrTo != nullptr)
	{
		if (newPerson == table[index].ptrTo->data.getName())
			throw std::invalid_argument("The name exist!\n");
		index = (index + 1) % table.size();
	}
	if (table[index].ptrTo == nullptr)
	{
		if (dance.add(Person(newPerson), table[index1].ptrTo, table[index2].ptrTo))
		{
			table[index].ptrTo = dance.lastAdded;
			size++;
		}
		else
			throw std::invalid_argument("The person can't be added!\n");
	}
}
/*
Try to remove a "name" in the dance through the hash 
If the remove isn't succsesfull std::invalid_argument is throwing
*/
void SystemHash::remove(const std::string & name)
{
	size_t index = getIndex(name);
	if (!dance.remove(table[index].ptrTo))
		throw std::invalid_argument("This won't be so easy!\n");
	erase(index);
}

///////////////////////////////////////////////
//Simple hash funtion,bad but in this homework working
size_t SystemHash::hashFunction(const std::string& str,const size_t size)
{
	
	size_t len = str.length();
	size_t res = len;
	for (size_t i=0;i<len;++i)
	{
		res += (unsigned char)str[i];
	}
	return res & (size - 1);
}
///The standart three functions for hash table
void SystemHash::insert(const std::string& name)
{
	size_t index = hashFunction(name, table.size());
	if (size *2 >= table.size())
	{
		rehash();
		index = hashFunction(name, table.size());
	}
	size_t tryies = table.size();
	while (--tryies && table[index].ptrTo != nullptr)
	{
		if (name == table[index].ptrTo->data.getName())
			throw std::invalid_argument("The name exist!\n");
		index = (index + 1) % table.size();
	}
	if (table[index].ptrTo == nullptr)
	{
		dance.addBack(Person(name));
		table[index].ptrTo = dance.lastAdded;
		size++;
	}
}

void SystemHash::erase(size_t index)
{
	size_t trys = table.size();
	size_t nextIndex = (index + 1) % table.size();
	while (table[nextIndex].ptrTo != nullptr && --trys)
	{
		std::swap(table[index], table[nextIndex]);
		index = (index + 1) % table.size();
		nextIndex = (nextIndex + 1) % table.size();
	}
	table[index].ptrTo = nullptr;
	--size;
}

int SystemHash::get(const std::string & name) const
{
	size_t index = hashFunction(name, table.size());
	size_t trys = table.size();//in case the table is full
	while (table[index].ptrTo != nullptr && trys--)
	{
		if (table[index].ptrTo->data.getName() == name)
			return index;
		index = (index + 1) % table.size();
	}
	return -1;
}


///////
//tmp functions
///////
size_t SystemHash::getIndex(const std::string & name) const
{
	int index = get(name);
	if (index == -1)
		throw std::invalid_argument("There isn't a such person!\n");
	return index;
}

void SystemHash::rehash()
{
	size_t newSize = table.size() * 2;
	HashTable newTable(newSize);

	for (size_t i = 0; i < table.size(); ++i)
	{
		if (table[i].ptrTo != nullptr)
		{
			size_t index = hashFunction(table[i].ptrTo->data.getName(), newSize);
			while (newTable[index].ptrTo != nullptr)
				index = (index + 1) % newSize;
			newTable[index].ptrTo = table[i].ptrTo;
		}
	}
	newTable.swap(table);
}

bool SystemHash::readFromFile(const char * fileName)
{
	std::fstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open())
		return false;
	while (!f.eof())
	{
		char name[MAX];
		f.getline(name, MAX);
		if (!f)
			return false;
		insert(name);
	}
	//everything from file is read->make the circle
	dance.connect();
	return true;
}
