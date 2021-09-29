#include <stdio.h>   /// for rand() calls
#include <stdlib.h>   /// for rand() calls
#include <assert.h>   /// for assert(<expr>)
#include <stdbool.h>  /// for boolean values: true, false  
#include <time.h>

#define MAX 30
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
        printf("%d ", x[i]);
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
                swap(&arr[j], &arr[j+1]);
                show(arr, size);
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
            swap(&arr[i], &arr[j]);
        }
    }

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



// merge sort
void merge(int *a, int l, int r, int n)
{
    int *b = (int *)malloc(n * sizeof(int)); /* dynamic memory must be freed */
    int c = l;
    int p1, p2;
    p1 = l;
    p2 = ((l + r) / 2) + 1;
    while ((p1 < ((l + r) / 2) + 1) && (p2 < r + 1))
    {
        if (a[p1] <= a[p2])
        {
            b[c++] = a[p1];
            p1++;
        }
        else
        {
            b[c++] = a[p2];
            p2++;
        }
    }

    if (p2 == r + 1)
    {
        while ((p1 < ((l + r) / 2) + 1))
        {
            b[c++] = a[p1];
            p1++;
        }
    }
    else
    {
        while ((p2 < r + 1))
        {
            b[c++] = a[p2];
            p2++;
        }
    }

    for (c = l; c < r - l + 1; c++) a[c] = b[c];

    free(b);
}

/** Merge sort algorithm implementation
 * @param a array to sort
 * @param n number of elements in the array
 * @param l index to sort from
 * @param r index to sort till
 */
void merge_sort(int *arr, int size, int left, int right)
{
    if (right - left == 1) {
        if (arr[left] > arr[right])
            swap(&arr[left], &arr[right]);
    }
    else if (left != right) {
        merge_sort(arr, size, left, (left + right) / 2);
        merge_sort(arr, size, ((left + right) / 2) + 1, right);
        merge(arr, left, right, size);
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
    //_bubble_sort(arr, MAX);
    //bubble_sort(arr, MAX);
    //quick_sort(arr, 0, MAX - 1);
    //insert_sort(arr, MAX);
    select_sort(arr, MAX);
    
    // BUG
    //merge_sort(arr, MAX, 0, MAX - 1);

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
