#include "mystring.h"
#include <stdio.h>
#include <stdbool.h>

int str_len(char *s) {
    int length = 0;
    
    while (s[length] != '\0') {
        length++;
    }
    
    return length;
}

int str_wc(char *s) {
    // your implementation
    int length = 0;
    int wordCount = 0;
    
    while (s[length] != '\0') {

        if (s[length] == ' ' && s[length-1] != ' ')
        {
            wordCount += 1;
        } 
        
        else if (s[length] != ' ' && s[length+1] == '\0') {
            wordCount += 1;
        }

        length++;
    }
    

    return wordCount-1;
}

void str_lower(char *s) {
    // your implementation
    if (s==NULL) return;

    char *p = s;

    while (*s) {
        if (*s >= 'A' && *s <= 'Z') {
            *s += 32;
        }
        s++;
    }

}

void str_trim(char *s) {

    // my soultion
    /**
     * 1. Remove leading spaces: Iterate through the string from the beginning and remove any leading spaces by shifting the remaining characters.
     * 
     * 2. Iterate through the string: For each character, check if the previous character is a letter and the next character 
     *    is a letter or the null terminator ('\0'). If this condition is met, it means the space should be ignored.
     * 
     * 3. Check for removal condition: If the condition in step 2 is not met, check if the previous character is a letter 
     *    and the current character is a space. If this condition is true, delete the space by shifting the remaining characters.
     * 
     * 4. Handle consecutive spaces: After removing a space, continue checking subsequent characters for consecutive spaces. 
     *    If more than one space is encountered, delete the extra spaces by shifting the remaining characters.
     * 
     * 5. Repeat the process: Iterate over the entire string again until there are no more spaces to trim.
    */

    // Remove leading spaces
    int i = 0;
    while (s[i] == ' ') {
        i++;
    }

    int j = 0;
    bool consecutiveSpace = false;

    while (s[i] != '\0') {
        if (s[i] != ' ') {
            s[j++] = s[i++];
            consecutiveSpace = false;
        } else {
            if (!consecutiveSpace) {
                s[j++] = ' ';
                consecutiveSpace = true;
            }
            i++;
        }
    }

    // Remove trailing spaces
    if (j > 0 && s[j - 1] == ' ') {
        j--;
    }

    s[j] = '\0';

}
