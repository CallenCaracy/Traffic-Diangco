#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "traffic.c"

int main(void){
    HeapPtrPriority heap;
    initBinaryHeap(&heap, 10);

    insert(&heap, newData(7, "PD"));
    insert(&heap, newData(12, "MR"));
    insert(&heap, newData(10, "D"));
    insert(&heap, newData(8, "PM"));
    insert(&heap, newData(11, "ML"));
    insert(&heap, newData(13, "DL"));
    insert(&heap, newData(13, "DR"));
    insert(&heap, newData(16, "M"));

    visualize(heap);
    // printf("Time: %d", timeUntilPMCrosses(heap));
    // delete(&heap);
    // visualize(heap);
    // printf("\n");
    // delete(&heap);
    // visualize(heap);
    // printf("\n");
    // delete(&heap);
    // visualize(heap);
    // printf("\n");
    // delete(&heap);
    // visualize(heap);
    
    // writeFile(heap);
    readFile();

    return 0;
}