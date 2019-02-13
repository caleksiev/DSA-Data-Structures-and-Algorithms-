#include "BHeap.h"


void BHeap::printRec(std::vector<int>tree,size_t index) const
{
	if (index >= tree.size())
		return;
	printRec(tree,getLeft(index));
	std::cout << tree[index] << " ";
	printRec(tree,getRight(index));
}

void BHeap::makeTreeRec(std::vector<int>& tree, size_t index) 
{
	if (index >= tree.size())
		return;
	makeTreeRec(tree,getLeft(index));
	tree[index] = data[0];
	extract();
	makeTreeRec(tree,getRight(index));
}

void BHeap::addElement(int data)
{
	this->data.push_back(data);

	size_t i = this->data.size() - 1;

	while (i > 0 && this->data[i] < this->data[getParrent(i)])
	{
		std::swap(this->data[i], this->data[getParrent(i)]);
		i = getParrent(i);
	}
}

void BHeap::extract()
{
	data[0] = data.back();
	data.pop_back();

	size_t i = 0;
	size_t s = getLeft(i);

	while (s < data.size())
	{
		if (s < data.size() - 1 && data[s + 1] < data[s])
			++s;
		if (data[s] > data[i])
			break;
		std::swap(data[s], data[i]);
		i = s;
		s = getLeft(i);
	}
}

void BHeap::getN(size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		int num;
		std::cin >> num;
		addElement(num);
	}
}

std::vector<int> BHeap::makeBST()
{
	std::vector<int> tree = data;
	makeTreeRec(tree, 0);
	return tree;
}
