#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

// 做公交车方案
int min_cost(int max_dist)
{
    // price table
    int a[] = {0, 12, 21, 31, 40, 49, 58, 69,79, 90, 101};
    int *f = NULL;
    int buf_size = sizeof(int) * (max_dist+1);
    f = malloc(buf_size);
    assert(f);
    memset(f, 0x3f, buf_size);
    f[0] = 0;
    for (int i = 1; i < sizeof(a)/sizeof(int); i++){
        printf("a[%2d]=%3d \n", i, a[i]);
    }
    for (int i = 1; i < sizeof(a)/sizeof(int); i++){
        for (int j = i; j <= max_dist; j++){
            if (f[j] > (f[j-i]+a[i])) {
                f[j] = f[j-i]+a[i];
            }
        }
    }
    printf("dist = %d, min_cost = %d\n", max_dist, f[max_dist]);
}

int main()
{
    //int a[] = {1,2,3,-9,4,3,-8,4,12,3,44,-30,4};
    int a[] = {-2,11,-4,13,-5,-2};
    int max = 0;
    max = max_sum(sizeof(a)/sizeof(int), a);
    printf("max sum = %d\n", max);
    min_cost(150);
}
