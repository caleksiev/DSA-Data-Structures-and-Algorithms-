#pragma once
#include<vector>
#include<iostream>
class BHeap
{
public:
	BHeap() = default;
	BHeap(const BHeap&other) = default;
	BHeap&operator=(const BHeap&other) = default;
	~BHeap() = default;
private:
	std::vector<int>data;
private:
	size_t getLeft(size_t index)const
	{
		return index * 2 + 1;
	}
	size_t getRight(size_t index)const
	{
		return index * 2 + 2;
	}
	size_t getParrent(size_t index)const
	{
		return (index - 1) / 2;
	}
private:
	void makeTreeRec(std::vector<int>&tree, size_t index);
private:
	void addElement(int data);
	void extract();
public:
	void getN(size_t N);
	std::vector<int>makeBST();
	void printRec(std::vector<int>tree, size_t index)const;
};
