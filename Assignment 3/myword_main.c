/*
--------------------------------------------------
Project: cp264oc-a3q2
File:    myword_main.c
About:   public test driver
Author:  HBF
Version: 2023-05-19
--------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

void display_word_summary(WORDSUMMARY *ws) {
  printf("%s:%d\n", "line_count", ws->line_count);
  printf("%s:%d\n", "word_count", ws->word_count);
  printf("%s:%d\n", "non_common_word_count", ws->non_common_word_count);
  int i;
  for (i = 0; i < ws->non_common_word_count; i++) {
    printf("%s:%d\n", ws->word_array[i].word, ws->word_array[i].frequency);
  }
}

int main(int argc, char *args[]) {  
  char infilename[40] = "textdata.txt"; //default input file name
  char stopwordfilename[40] = "common-english-words.txt"; //default stop word file
  if (argc > 1) {  
	if (argc >= 2) strcpy(infilename, args[1]);
	if (argc >= 3) strcpy(stopwordfilename, args[2]);
  }

  // create a stopword dictionary by an array of strings
  char stopword_arrays[26][100] = {0};
  char *stopwords[26]; 
  int i;
  for (i=0; i<26; i++) {
    stopwords[i] = &stopword_arrays[i][0];
  }
  stopword_dictionay(stopwordfilename, stopwords);
  printf("is_stopword(%s):%d\n","is", is_stopword(stopwords, "is"));
  printf("is_stopword(%s):%d\n","hello", is_stopword(stopwords, "hello"));
  
  // word data processing
  WORDSUMMARY wordsummary = {0}; 
  process_word(infilename, &wordsummary, stopwords);  
  display_word_summary(&wordsummary);
  return 0;
}


