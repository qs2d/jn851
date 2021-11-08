#include <stdio.h>

int max_sum(int n, int a[])
{
    int sum = 0, b = 0;
    for(int i = 0; i < n; i++){
        if(b > 0)
            b += a[i];
        else
            b = a[i];
        if (b > sum)
            sum = b;
    }
    printf("max_sum = %d %d\n", n, sum);
    return sum;
}

int main()
{
    //int a[] = {1,2,3,-9,4,3,-8,4,12,3,44,-30,4};
    int a[] = {-2,11,-4,13,-5,-2};
    int max = 0;
    max = max_sum(sizeof(a)/sizeof(int), a);
    printf("max sum = %d\n", max);
}
