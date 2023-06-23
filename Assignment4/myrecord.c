/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "mysort.h"
#include "myrecord.h"

#define MAX_LINE 100

GRADE grade(float score){
  GRADE r = {"F", 0};
  int p = (int)round(score);
  r.percentage = p;
  
  if (p >= 90) strcpy(r.letter_grade, "A+");
  else if (p >= 85) strcpy(r.letter_grade, "A");
  else if (p >= 80) strcpy(r.letter_grade, "A-");
  else if (p >= 75) strcpy(r.letter_grade, "B+");
  else if (p >= 70) strcpy(r.letter_grade, "B");
  else if (p >= 65) strcpy(r.letter_grade, "B-");
  else if (p >= 60) strcpy(r.letter_grade, "C+");
  else if (p >= 55) strcpy(r.letter_grade, "C");
  else if (p >= 50) strcpy(r.letter_grade, "C-");
  else if (p >= 45) strcpy(r.letter_grade, "D+");
  else if (p >= 40) strcpy(r.letter_grade, "D");
  else strcpy(r.letter_grade, "F");

  return r;
}

// created an axiulry function 
int compare_floats(const void* a, const void* b) {
  const float* fa = (const float*)a;
  const float* fb = (const float*)b;
  return (*fa > *fb) - (*fa < *fb);
}


STATS process_data(RECORD *dataset, int n) {    
  STATS result = {0, 0, 0, 0};

  // Calculate count
  result.count = (float)n;

  // Calculate mean
  for (int i = 0; i < n; i++) {
    result.mean += dataset[i].score;
  }
  result.mean /= (float)n;

  // Calculate standard deviation
  for (int i = 0; i < n; i++) {
    result.stddev += pow(dataset[i].score - result.mean, 2);
  }
  result.stddev = sqrt(result.stddev / (float)n);

  // Calculate median
  float* scores = (float*)malloc(n * sizeof(float));
  for (int i = 0; i < n; i++) {
    scores[i] = dataset[i].score;
  }
  qsort(scores, n, sizeof(float), compare_floats);

  if (n % 2 == 0) {
    result.median = (scores[n / 2 - 1] + scores[n / 2]) / 2.0f;
  } else {
    result.median = scores[n / 2];
  }

  free(scores);
  return result;
}


int import_data(char *infilename, RECORD *dataset) {
  FILE *file = fopen(infilename, "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return 0;
  }

  char line[MAX_LINE];
  int count = 0;
  while (fgets(line, MAX_LINE, file) != NULL) {
    sscanf(line, "%s %f", dataset[count].name, &dataset[count].score);
    count++;
  }

  fclose(file);
  return count;
}


int report_data(char *outfilename, RECORD dataset[], STATS stats) {
  FILE *file = fopen(outfilename, "w");

  fprintf(file, "Name\t\tScore\t%%\tGrade\n");
  for (int i = 0; i < stats.count; i++) {
    GRADE g = grade(dataset[i].score);
    int percentage = (int)ceil(dataset[i].score);
    fprintf(file, "%-10s\t%.2f\t%.0d\t%s\n", dataset[i].name, dataset[i].score, percentage, g.letter_grade);
  }

  fclose(file);
  return 1;
}


