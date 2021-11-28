#include <stdio.h>   /// for rand() calls
#include <stdlib.h>   /// for rand() calls
#include <assert.h>   /// for assert(<expr>)
#include <stdbool.h>  /// for boolean values: true, false  
#include <time.h>

#define MAX 10
#define _swap(a,b) (a^=b,b^=a,a^=b)
#define DEBUG 1

void gen_rand_array(int x[], int size, int max)
{
    srand(time(0));
    for (int i = 0; i < size; i++) {
        x[i] = rand() % max;
    }
}

void show(int x[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%2d ", x[i]);
        if ( i > 1 && i%30 == 0){
            if (DEBUG == 1) {
                printf("\n");
            }
        }
    }
    printf("\n");
}

void show_color(int x[], int n, int left, int right)
{
    for (int i = 0; i < n; i++) {
        if (i == left || i == right){
            printf("\033[31m%2d\033[0m ", x[i]);
        }else{
            printf("%2d ", x[i]);
        }

        if ( i > 1 && i%30 == 0){
            if (DEBUG == 1) {
                printf("\n");
            }
        }
    }
    printf("\n");
}



void check_array(int x[], int max)
{
    /* check if array ir correctly ordered */	
    for (int i = 0; i < max - 1; i++) {
        assert(x[i] <= x[i+1]);
    }
}

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

// bubble sort
//
void bubble_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++){
        for( int j = 0; j < size - 1 - i; j++){
            if (arr[j] > arr[j+1]){
                show_color(arr, MAX, j, j + 1);
                swap(&arr[j], &arr[j+1]);
                //show(arr, size);
            }
        }
    }
}

void _bubble_sort(int arr[], int size)
{
	bool is_sorted = false;
    while (!is_sorted) {
		is_sorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i+1]);
                show(arr, size);
                is_sorted = false;
            }
        }
    }
}

// quick sort
int partition(int arr[], int lower, int upper)
{
    // ?
    int i = (lower - 1);
    int pivot = arr[upper];  
    for (int j = lower; j < upper; j++) {
        if (arr[j] <= pivot) {  
            i++;  // increment the index of smaller element
            show_color(arr, MAX, i, j);
            swap(&arr[i], &arr[j]);
        }
    }

    show_color(arr, MAX, i + 1, upper);
    swap(&arr[i + 1], &arr[upper]);  
    return (i + 1);
}

void quick_sort(int arr[], int lower, int upper)
{
    if (upper > lower) {
        int pindex = partition(arr, lower, upper);
        quick_sort(arr, lower, pindex - 1);
        quick_sort(arr, pindex + 1, upper);
    }
}


// insert sort
void insert_sort(int arr[], int size)
{
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        int key = arr[i];
        /* Move all elements greater than key to one position */
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        /* Find a correct position for key */
        arr[j + 1] = key;
        show(arr, size);
    }
}

// select sort
void select_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(arr + i, arr + min_index);
            show(arr, size);
        }
    }
}




// merge short
void merge(int *num, int start, int mid, int end)
{
    int *temp = (int *)malloc((end-start+1) * sizeof(int));    //申请空间来存放两个有序区归并后的临时区域
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end) {
        if (num[i] <= num[j]) {
            temp[k++] = num[i++];
        } else {
            temp[k++] = num[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = num[i++];
    }

    while (j <= end) {
        temp[k++] = num[j++];
    }

    //将临时区域中排序后的元素，整合到原数组中
    for (i = 0; i < k; i++) {
        num[start + i] = temp[i];
    }

    free(temp);
}

/* 将序列对半拆分直到序列长度为1*/
void merge_sort(int *num, int start, int end)
{
    int mid = start + (end - start) / 2;

    if (start >= end) {
        return;
    }

    merge_sort(num, start, mid);
    merge_sort(num, mid + 1, end);

    merge(num, start, mid, end);
}

void shell_sort(int arr[], int len)
{
    int i, j, gap;

    for (gap = len / 2; gap > 0; gap = gap / 2)
        for (i = gap; i < len; i++)
            for (j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j = j - gap){
                show_color(arr, MAX, j, j + gap);
                swap(&arr[j], &arr[j + gap]);
            }
}



static void test() {
    /* simple int array for testing */
	//int arr[MAX] = {0};
    int *arr = (int *)malloc(sizeof(int) * MAX);

    gen_rand_array(arr, MAX, MAX);
    //check_array(arr, MAX);

    printf("\nbefore sort\n");
    show(arr, MAX);
    
    /* sort array */
    // bubble_sort(arr, MAX);
    //bubble_sort(arr, MAX);
    quick_sort(arr, 0, MAX - 1);
    //insert_sort(arr, MAX);
    //select_sort(arr, MAX);
    
    // merge_sort(arr, MAX, 0, MAX - 1);
    // merge_sort(arr, 0, MAX);
    // shell_sort(arr, MAX);

    printf("\nafter sort\n");
    show(arr, MAX);

    check_array(arr, MAX);
    free(arr);

}

int main()
{
    test();  // run self-test implementations
    return 0;
}
