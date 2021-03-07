#include <stdlib.h>
#include <stdio.h>


void Quicksort(int elems[], int size);


int main(){
    int lst[] = {8, 7, 6, 1, 0, 9, 2};
    int size = sizeof(lst) / sizeof(lst[0]);
   
    for (int i = 0; i < size; i++){
        printf("%d ", lst[i]);
    }

    Quicksort(lst, size);
    
    printf("\n-----------\n");

    for (int i = 0; i < size; i++){
        printf("%d ", lst[i]);
    }

    return 0;
}


void Quicksort(int elems[], int size){
    int left, right, pivot, aux;

    pivot = size - 1;

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
    
        right++;

        if (right == pivot){
            aux = elems[left];
            elems[left] = elems[pivot];
            elems[pivot] = aux;

            break;
        }
    }

    int leftArray[left];

    for(int i = 0; i < left; i++){
        leftArray[i] = elems[i];
        printf("Left: %d\n", leftArray[i]);
    }

    Quicksort(leftArray, left + 1);

    int rightArray[size - left - 1];

    for(int i = 0; i < size - left - 1; i++){
        rightArray[i] = elems[size - left + i];
    }

    Quicksort(rightArray, size - left - 1);

}
