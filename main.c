#include <stdlib.h>
#include <stdio.h>


void Quicksort(int elems[], int size);


int main(){
    //int lst[] = {8, 7, 6, 1, 0, 9, 2}; //Original test list
    int lst[] = {84, 58, 22, 37, 30, 49, 79, 41, 60, 83, 65, 95, 73, 33, 87, 62, 46, 85, 28, 16};
    int size = sizeof(lst) / sizeof(lst[0]);

    printf("Unsorted: ");
    for (int i = 0; i < size; i++){
        printf("%d ", lst[i]);
    }

    Quicksort(lst, size);

    printf("\n-----------\n");

    printf("Sorted: ");
    for (int i = 0; i < size; i++){
        printf("%d ", lst[i]);
    }

    return 0;
}


void Quicksort(int elems[], int size){
    int left, right, pivot, minusSize, aux;
    minusSize = size - 1;

    pivot = minusSize;

    if (size == 1){
        return;
    }

    for (int i = 0; i < size; i++){
        if (elems[i] > elems[pivot]){
            left = i;
            break;
        }
    }

    right = left + 1;

    while(1){
        if (elems[right] < elems[left] && elems[right] < elems[pivot]){
            aux = elems[left];

            elems[left] = elems[right];
            elems[right] = aux;

            left++;
        }

        if (right == pivot){
            aux = elems[left];
            elems[left] = elems[pivot];
            elems[pivot] = aux;

            break;
        }

        right++;
    }

    if (left > 0){
        int leftArray[left];

        for (int i = 0; i < left; i++){
            leftArray[i] = elems[i];
        }

        Quicksort(leftArray, left);

        for (int i = 0; i < left; i++){
            elems[i] = leftArray[i];
        }
    }

    int rightArray[size - left - 1];

    for (int i = 0; i < size - left - 1; i++){
        rightArray[i] = elems[left + i + 1];
    }

    Quicksort(rightArray, size - left - 1);

    for (int i = 0; i < size - left - 1; i++){
        elems[left + i + 1] = rightArray[i];
    }
}
