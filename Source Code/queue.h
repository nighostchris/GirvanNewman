#ifndef QUEUE_H
#define QUEUE_H

struct node
{
	int node_no;
	node* next;
};

class Queue
{
	private:
		node* top;
		node* bottom;
	public:
		Queue();
		~Queue();

		void enqueue(int node_no);
		int dequeue();
		bool checkEmpty() const;
};

#endif
