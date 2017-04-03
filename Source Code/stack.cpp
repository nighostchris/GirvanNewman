#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack(int size) : currentSize(0)
{
	stacking = new int[size];
	for (int i = 0; i < size; i++)
		stacking[i] = 0;
}

Stack::~Stack()
{
	delete [] stacking;
}

void Stack::push(int node_no)
{
	stacking[currentSize] = node_no;
	currentSize++;
}

int Stack::pop()
{
	currentSize--;
	int result = stacking[currentSize];
	stacking[currentSize] = 0;
	return result;
}

bool Stack::checkEmpty()
{
	if (currentSize == 0)
		return true;
	return false;
}
