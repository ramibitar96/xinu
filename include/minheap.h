/* Credit for this min-heap goes to Robin Thomas, code found at https://github.com/robin-thomas/min-heap/blob/master/minHeap.c */
/* Combined with code from  http://www.sanfoundry.com/java-program-implement-min-heap/*/
#ifndef HSIZE
#define HSIZE 100
#endif

struct heapNode
{
	pid32 pid;
	uint32 key;
};

extern struct heapNode minHeap[];

void minHeapify(int pos);
void swap(int fpos, int spos);
int lChild(int x);
int rChild(int x);
int parent(int x);
