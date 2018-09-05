/* Credit for this min-heap goes to Robin Thomas, code found at https://github.com/robin-thomas/min-heap/blob/master/minHeap.c */
/* Combined with code from  http://www.sanfoundry.com/java-program-implement-min-heap/*/
#include <xinu.h>

//creates the new heap, return OK or SYSERR. 
int heapSize;

status newheap()
{
	heapSize = 0;
    return OK;
}

//insert a process of PID with the given key into the heap 
status heapinsert(pid32 pid, uint32 key) 
{
	minHeap[heapSize].pid = pid;
    minHeap[heapSize].key = key;
	int current = heapSize;
	// kprintf("size before ++ %d\n", heapSize);
    heapSize++;

	while(minHeap[current].key < minHeap[parent(current)].key)
	{
        // kprintf("current: %d, parent %d\n", current, parent(current));
		swap(current, parent(current));			
		current = parent(current);
	}
    return OK;
}

//removes the root node and return its process id.
pid32 heapgethead() 
{
    pid32 returnPid;
    if (heapSize == 1) 
    {
        returnPid = minHeap[0].pid;
        minHeap[0].pid = NULL;
        return returnPid;
    } 
    else 
    {
       returnPid = minHeap[0].pid;
	   minHeap[0] = minHeap[(heapSize - 1)];
       minHeap[(heapSize - 1)].pid = NULL;
       minHeap[(heapSize - 1)].key = 0;
       heapSize--;
	   minHeapify(0);
	   return returnPid;
    }
}

//returns the key value at the root node of the heap without removing the node.
int32 heapminkey() 
{
    if (heapSize == 0)
        return 0;
	return minHeap[0].key;
}

pid32 heapgetitem(pid32 pid)
{
	int current;
	for (current = 0; current < heapSize; current++) {
		if (minHeap[current].pid == pid) {
			minHeap[current] = minHeap[--heapSize];
			minHeapify(current);
			return pid;
		}
	}
	return SYSERR;
}


void minHeapify(int pos)
{
	//checks if it is a leaf
    if (pos > ((heapSize - 1)/ 2)  &&  pos <= heapSize)
    { 
    	/*do nothing heap is done re-sorting*/
    } 
    else
    {
        if ((minHeap[lChild(pos)].key != NULL && minHeap[pos].key > minHeap[lChild(pos)].key)  || (minHeap[lChild(pos)].key != NULL && minHeap[pos].key > minHeap[rChild(pos)].key))
        {
        	if (minHeap[lChild(pos)].key != NULL && minHeap[rChild(pos)].key != NULL)
        	{
            	if (minHeap[lChild(pos)].key < minHeap[rChild(pos)].key)
           	 	{
            		swap(pos, lChild(pos));
                	minHeapify(lChild(pos));
            	}         
            	else
     	    	{
            	    swap(pos, rChild(pos));
               		minHeapify(rChild(pos));
            	}
            }
            else if (minHeap[lChild(pos)].key != NULL) 
            {
            	swap(pos, lChild(pos));
                minHeapify(lChild(pos));
            }
        }
    }
}

void swap(int fpos, int spos)
{
    pid32 tempPid = minHeap[fpos].pid;
    uint32 tempKey = minHeap[fpos].key;
    minHeap[fpos] = minHeap[spos];
    minHeap[spos].pid = tempPid;
    minHeap[spos].key = tempKey;
}

int lChild(int x) 
{
	return 2 * x + 1;
}

int rChild(int x) 
{
	return 2 * x + 2;
}

int parent(int x)
{
	return (x-1) / 2;
} 