#ifndef STACK_H_
#define STACK_H_

class Stack
{
	private:
		int currentSize; // No. of elements inside stack
		int* stacking; // pointer to the stack array
	public:
		Stack(int size); // constructor of Stack
		~Stack(); // destructor of Stack

		void push(int node_no); // Add element into Stack
		int pop(); // Return the top element from the Stack
		bool checkEmpty(); // check if the Stack is empty
};

#endif
