/*
--------------------------------------------------
Project: cp264oc-a4q1 
File:    mysort_main.c, 
About:   public test driver for mysort.c
Author:  HBF
Version: 2023-05-30
--------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>  
#include "mysort.h"

typedef enum {false, true} BOOLEAN;
BOOLEAN is_sorted(float *a[], int left, int right);
// display data by pointer array
void display_array(float *a[], int left, int right);
// copy data addresses to array of pointers  
void copy_data_address(float d[], float *a[], int left, int right);


int main(int argc, char *args[])
{ 
  float d[] = {3, 1, 4, 5, 2, 7, 6, 9, 8}; // test data array 
  int i, n = sizeof(d)/sizeof(float);      // array length
  float *a[n];                             // pointer array to sort
  
  printf("Algorithm correctness testing:\n");  
  printf("given data d[]:");  
  copy_data_address(d, a, 0, n-1);
  display_array(a, 0, n-1);
  printf("\n"); 
  printf("is_sorted(a):%d\n", is_sorted(a, 0, n-1));    
    
  // testing selection sort  
  copy_data_address(d, a, 0, n-1);
  select_sort(a, 0, n-1);  
  printf("after select_sort(a):");
  display_array(a, 0, n-1);
  printf("\nafter select_sort(a) is_sorted(a):%d\n", is_sorted(a, 0, n-1));  

  // testing quick sort
  copy_data_address(d, a, 0, n-1);
  quick_sort(a, 0, n-1);    
  printf("after quick_sort(a):");
  display_array(a, 0, n-1);
  printf("\nafter quick_sort(a) is_sorted(a):%d\n", is_sorted(a, 0, n-1));  
  
  return 0;
} 

BOOLEAN is_sorted(float *a[], int left, int right)
{
  int i;
  for (i=left; i<right; i++) {
    if (*a[i+1] < *a[i]) {
		return false;
	}
  }
  return true;
}

void display_array(float *a[], int left, int right)
{
  int i; 
  if (left<=right) 
	  printf("%.0f", *a[0]);
  if (left<right)
  for (i=left+1; i<=right; ++i) {
    printf(",%.0f", *a[i]);
  }
}

void copy_data_address(float d[], float *a[], int left, int right)
{
  int i;
  for (i = left; i <= right; i++)
    a[i] = &d[i]; 
}



