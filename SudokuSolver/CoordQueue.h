#pragma once
#ifndef CoordQueue_h

typedef struct {
	size_t x;
	size_t y;
} Coord;
typedef struct {
	Coord coordinate;
	struct QNode* next;
} QNode;

class Queue {
private:
	QNode head, tail;
public:
	/*
	Allocate memory for the Queue head and tail and initialize it
	*/
	Queue queue(Coord* coordinate);

	void destroy(Queue* queue);
};
#endif