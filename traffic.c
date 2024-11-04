#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "traffic.h"

void initBinaryHeap(HeapPtrPriority *head, int max){
    *head = malloc(sizeof(BinaryHeapPriority));
    if(*head == NULL){
        return;
    }

    (*head)->count = 0;
    (*head)->max = max;
    (*head)->elems = malloc(sizeof(TrafficData) * max);
    if((*head)->elems == NULL){
        free(*head);
        return;
    }
    for(int i = 0; i < (*head)->max; i++){
        (*head)->elems[i].time = 0;
        (*head)->elems[i].lane = 0;
    }
}

bool isEmpty(HeapPtrPriority head){
    return head->count == 0;
}

bool isFull(HeapPtrPriority head){
    return head->count == head->max;
}

bool insert(HeapPtrPriority *head, TrafficData data){
    if(isFull(*head)){
        printf("Full.");
        return false;
    }

    int i = (*head)->count;
    (*head)->elems[i] = data;
    (*head)->count++;

    while(i > 0){
        int parent = (i - 1) / 2;
        
        if((*head)->elems[i].lane < (*head)->elems[parent].lane){
            TrafficData temp = (*head)->elems[i];
            (*head)->elems[i] = (*head)->elems[parent];
            (*head)->elems[parent] = temp;
            i = parent;
        }else{
            break;
        }
    }
    return true;
}

bool delete(HeapPtrPriority *head){
    if(isEmpty(*head)){
        printf("The array is empty");
        return false;
    }

    int lastIndex = (*head)->count - 1;
    (*head)->elems[0] = (*head)->elems[lastIndex];
    (*head)->count--;

    heapifyDown(head, 0);

    return true;
}

void heapifyDown(HeapPtrPriority *head, int i){
    int highPrio = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < (*head)->count && (*head)->elems[leftChild].lane < (*head)->elems[highPrio].lane) {
        highPrio = leftChild;
    }

    if (rightChild < (*head)->count && (*head)->elems[rightChild].lane < (*head)->elems[highPrio].lane) {
        highPrio = rightChild;
    }

    if (highPrio != i) {
        TrafficData temp = (*head)->elems[i];
        (*head)->elems[i] = (*head)->elems[highPrio];
        (*head)->elems[highPrio] = temp;

        heapifyDown(head, highPrio);
    }
}

void visualize(HeapPtrPriority head){
    if(isEmpty(head)){
        return;
    }

    for (int i = 0; i < head->count; i++){
        printf("Priority: %d, Time: %d, Type: %s\n", head->elems[i].lane, head->elems[i].time, translateEnumToChar(head->elems[i].lane));
    }

    printf("Time PM Crossed: %dsec\n\n", timeUntilPMCrosses(head));
}

const char* translateEnumToChar(Entity lane){
    switch(lane){
        case 1:
            return "M";
        case 2:
            return "D";
        case 3:
            return "ML";
        case 4:
            return "DL";
        case 5:
            return "MR";
        case 6:
            return "DR";
        case 7:
            return "PM";
        case 8:
            return "PD";
        default:
            return "NA";
    }
}

Entity charToEnum(char* c){
    if(strcmp(c, "M") == 0){
        return M;
    }else if(strcmp(c, "D") == 0){
        return D;
    }else if(strcmp(c, "ML") == 0){
        return ML;
    }else if(strcmp(c, "DL") == 0){
        return DL;
    }else if(strcmp(c, "MR") == 0){
        return MR;
    }else if(strcmp(c, "DR") == 0){
        return DR;
    }else if(strcmp(c, "PM") == 0){
        return PM;
    }else if(strcmp(c, "PD") == 0){
        return PD;
    }else{
        return -1;
    }
}

TrafficData newData(int time, char *type){
    TrafficData td;

    td.lane = charToEnum(type);
    td.time = time;

    return td;
}

void writeFile(const HeapPtrPriority head){
    FILE *f = fopen("traffic.dat", "wb");
    int timePMCrossed = timeUntilPMCrosses(head);

    if(f != NULL){
        fwrite(&head->count, sizeof(int), 1, f);
        fwrite(&head->max, sizeof(int), 1, f);
        fwrite(head->elems, sizeof(TrafficData), head->count, f);
        fwrite(&timePMCrossed, sizeof(int), 1, f);
        fclose(f);
    }
}

void readFile(){
    FILE *f = fopen("traffic.dat", "rb");
    TrafficData holder;
    int timePMCrossed;

    if(f != NULL){
        int count, max;

        fread(&count, sizeof(int), 1, f);
        fread(&max, sizeof(int), 1, f);

        printf("Reading...\n");
        for(int i = 0; i < count; i++){
            fread(&holder, sizeof(TrafficData), 1, f);
            printf("Priority: %d, Time: %d, Type: %s\n", holder.lane, holder.time, translateEnumToChar(holder.lane));
        }

        fread(&timePMCrossed, sizeof(int), 1, f);
        printf("\nTime until PM Crossed: %dsec", timePMCrossed);
        fclose(f);
    }
}

int timeUntilPMCrosses(HeapPtrPriority head){
    HeapPtrPriority temp;
    initBinaryHeap(&temp, head->max);

    for(int i = 0; i < head->count; i++){
        temp->elems[i] = head->elems[i];
    }
    temp->count = head->count;
    temp->max = head->max;

    int time = 0;

    while(!isEmpty(temp)){
        if(temp->elems[0].lane == charToEnum("PM")){
            break;
        }else{
            time += temp->elems[0].time;
            delete(&temp);
        }
    }

    free(temp->elems);
    free(temp);

    return time;
}