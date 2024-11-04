#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <stdbool.h>

typedef enum {
    M = 1, D, ML, DL, MR, DR, PM, PD
}Entity;

typedef struct{
    Entity lane;
    int time;
}TrafficData;

typedef struct {
    TrafficData *elems;
    int count;
    int max;
}BinaryHeapPriority, *HeapPtrPriority;

TrafficData newData(int time, char *type);
const char* translateEnumToChar(Entity lane);
Entity charToEnum(char* c);
void initBinaryHeap(HeapPtrPriority *head, int max);
bool isEmpty(HeapPtrPriority head);
bool isFull(HeapPtrPriority head);
bool insert(HeapPtrPriority *head, TrafficData data);
bool delete(HeapPtrPriority *head);
void heapifyDown(HeapPtrPriority *head, int i);
void visualize(HeapPtrPriority head);
void writeFile(const HeapPtrPriority head);
void readFile();
int timeUntilPMCrosses(HeapPtrPriority head);

#endif