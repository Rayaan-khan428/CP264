/*
 * your program signature
 */ 
 
#ifndef MYWORD_H
#define MYWORD_H

#define MAX_WORD 30
#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

typedef struct word {
    char word[MAX_WORD];
    int frequency;
} WORD;

typedef struct words {
    WORD word_array[MAX_WORDS];
    int line_count;
    int word_count;
    int non_common_word_count;
} WORDSUMMARY;

void stopword_dictionay(char *filename, char *stopwords[]);
int is_stopword(char *stopwords[], char *word);
int process_word(char *filename, WORDSUMMARY *words, char *stopwords[]);

#endif