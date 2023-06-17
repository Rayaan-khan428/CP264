/*
--------------------------------------------------
Project: cp264oc-a5q1
File:    myrecord_llist_main.c   public test driver
Author:  HBF
Version: 2023-06-06
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 
#include "myrecord_sllist.h"

typedef struct {
  float count;
  float mean;
  float stddev;
  float median;
} STATS;

int import_data(SLL *sllp, char *infilename);
STATS process_data(SLL *sllp);
void searh_message(NODE *p, char *name);
void sll_display(SLL *sllp);
void select_sort(float *a[], int left, int right);


int main(int argc, char* args[]) {
  char infilename[40] = "marks.txt";
  if (argc >= 2) strcpy(infilename, args[1]);

  printf("\nImport and display\n");
  SLL sllist = {0};
  import_data(&sllist, infilename);
  sll_display(&sllist);

  // testing insert and search
  printf("\nInsert and search\n");
  char name[20] = "Moore";
  sll_insert(&sllist, name, 92.0);
  NODE *p = sll_search(&sllist, name);
  searh_message(p, name);
  
  printf("\nDelete and search\n");
  strcpy(name, "Wang");
  sll_delete(&sllist, name);
  p = sll_search(&sllist, name);
  searh_message(p, name);
 
  printf("\nProcess data\n");
  STATS stats = process_data(&sllist);
  printf("count:%.1f\n", stats.count);
  printf("mean:%.1f\n", stats.mean);
  printf("stddev:%.1f\n", stats.stddev);
  printf("median:%.1f\n", stats.median);
  
  printf("\nClean\n");
  sll_clean(&sllist);
  printf("length:%d\n", sllist.length);
  
  return 0;
}

void searh_message(NODE *p, char *name) {
  if (p == NULL)
    printf("%s:NULL\n", name);
  else
    printf("%s:%.1f\n", p->data.name, p->data.score);
}

void select_sort(float *a[], int left, int right)
{
  int i, j, k; 
  float *temp;
  for (i = left; i <= right; ++i) {
	k = i;
    for(j = i+1; j <= right; ++j) {
	  if (*a[j] < *a[k]) {
		k = j;
	  }
	}
    if (i != k) {
      temp = a[k];
      a[k] = a[i];
      a[i] = temp;  
    }
  }
}
  
float median(SLL *sllp)
{
  if (sllp->start == NULL) return 0;
  NODE *np = sllp->start;
  int i=0, n = sllp->length;
  float *a[n];
  while (np) {
    a[i] = &(np->data.score);
    np = np->next;
    i++;
  }
  select_sort(a, 0, n-1);
  return (n % 2 == 1)? *a[n/2] : (*a[n/2-1] + *a[n/2])/2 ;   
} 

STATS process_data(SLL *sllp) {
  int count = 0;
  float mean = 0;
  float stddev = 0;
  NODE *np = sllp->start;
  while (np != NULL) {
    count++;
    mean += np->data.score;
    stddev += np->data.score * np->data.score ;
    np = np->next;
  }
  mean /= count;
  stddev = sqrt(stddev/count - mean*mean);
  
  STATS stats = {};
  stats.count = count;
  stats.mean = mean;
  stats.stddev = stddev;
  stats.median = median(sllp);
  return stats;	
}
 
int import_data(SLL *sllp, char *filename) {
  char line[40], name[40];
  char *valuestr = NULL;
  char delimiters[] = ",";
  float score = 0;

  FILE *fp = fopen(filename, "r");  
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    return 0;
  }
  while (fgets(line, sizeof(line), fp) != NULL) {
    valuestr = strtok(line, delimiters);
    strcpy(name, valuestr);
    valuestr = strtok(NULL, delimiters);
    score = atof(valuestr);
	if (strlen(name)>0 && score >0 ) // validate data
      sll_insert(sllp, name, score);
  }
  fclose(fp);
  return sllp->length;
}


void sll_display(SLL *sllp) {
	NODE *np = sllp->start;
	printf("length:%d\n", sllp->length);
	while (np != NULL) {
		printf("%s,%.1f\n", np->data.name, np->data.score);
		np = np->next;
	}
}
