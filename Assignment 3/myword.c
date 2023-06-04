/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

void stopword_dictionay(char *filename, char *stopwords[])
{
    // your implementation
    FILE *fp = fopen(filename, "r");

    char line[1000]; // store the line of text read
    char delimiters[] = " .,\n\t\r"; // a string of delimiters used to tokenize the input text
    char *token; // a pointer variable that is used to store each tokenized word
    int i; // represent index of the stop word dictionary

    while (fgets(line, 1000, fp) != NULL) {

        //strtok is a tokenization function that takes two arguments, an initial string to be parsed and a const delimiter, returning a pointer to the first char of a token or null
        token = (char*) strtok(line, delimiters);
        
        while (token != NULL) { // might be source of error -----------------------------------
            i = (int)(*token - 'a');
            strcat(stopwords[i],token); // concatenate the two strings
            strcat(stopwords[i],",");
            token = (char*)strtok(NULL, delimiters);
        }

    }
    
}

int is_stopword(char *stopwords[], char *word)
{   
    int size = 0;

    // Calculate the size of the stopwords array
    while (stopwords[size] != NULL) {
        size++;
    }
    
    for (int i = 0; i < size; i++) {
        char* currentStopword = stopwords[i];
        char* token = strtok(currentStopword, ",");
        
        while (token != NULL) {
            if (strcmp(token, word) == 0) {
                return 1; // Word found in the array
            }
            token = strtok(NULL, ",");
        }
    }
    return 0; // Word not found in the array

}

int process_word(char *filename, WORDSUMMARY *words, char *stopwords[]) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    char delimiters[] = " \t\n";
    char *word_token;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        words->line_count++;
        str_lower(line);
        str_trim(line);

        word_token = strtok(line, delimiters);
        while (word_token != NULL) {
            if (is_stopword(stopwords, word_token) == 0) {
                strcpy(words->word_array[words->word_count].word, word_token);
                words->word_array[words->word_count].frequency++;
                words->word_count++;
            }
            word_token = strtok(NULL, delimiters);
        }
    }

    fclose(fp);
    return 0;
}

