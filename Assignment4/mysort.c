/*
 * your program signature
 */ 

#include "mysort.h"


void select_sort(float *a[], int left, int right)
{
    // your implementation
    int i, j, k;
    float *temp;

    for (i=left; i<right; i++) {

        k = i;

        for (j = i+1; j<right; j++) {

            if (*a[j] < *a[k]) {
                k = j;
            }
        }

        if (i != k) {
            // swaping the address a[k] and a[i]
            temp = a[k];
            a[k] = a[i];
            a[i] = temp;
        }
    }
}

void quick_sort(float *a[], int left, int right)
{
    int i, j;
    float key, *temp;

    if (left < right)
    {
        key = *a[left];
        i = left + 1;
        j = right;

        while (i <= j)
        {
            while (i <= right && *a[i] <= key)
                i++;
            while (j >= left && *a[j] > key)
                j--;

            if (i < j)
            {
                // Swap a[i] and a[j] without using swap function
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        // Swap a[left] and a[j] without using swap function
        temp = a[left];
        a[left] = a[j];
        a[j] = temp;

        quick_sort(a, left, j - 1);
        quick_sort(a, j + 1, right);
    }
}
