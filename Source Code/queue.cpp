#include <iostream>
#include "queue.h"

using namespace std;

Queue::Queue() : top(NULL), bottom(NULL)
{ 
}

Queue::~Queue()
{
}

void Queue::enqueue(int node_no)
{
    node* update = new node;
    update->node_no = node_no;
    update->next = NULL;
    if (top == NULL)
        top = update;
    else
        bottom->next = update;
    bottom = update;
}

int Queue::dequeue()
{
    int value = 0;
    if (top == NULL)
        return value;
    else
    {
        node* temp = top;
        value = top->node_no;
        top = top->next;
        delete temp;
        return value;
    }
}

bool Queue::checkEmpty() const
{
	if (top == NULL)
		return true;
	return false;
}
