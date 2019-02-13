#include"BHeap.h"

int main()
{
	BHeap heap;
	size_t N;
	std::cin >> N;
	heap.getN(N);
	std::vector<int> bst = heap.makeBST();
	heap.printRec(bst, 0);
	return 0;
}