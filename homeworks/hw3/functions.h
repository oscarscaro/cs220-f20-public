#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <stdio.h>

#define MAX_INPUT_SIZE 128
#define MAX_WORD_SIZE 32
#define DEFAULT_RESTRICTION 10

/** Function to read data from file pointer into words array.
 *  @param fp the filepointer to search words file.
 *  @param words is the 2D character array of words
 *  @param size is the expected number of words in the file.
 *  @return 0 if no issues, 1 if there are issues.
 */
int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size);

/** Match function to check whether regex matches a word.
 * @param regex, is a null terminated char array of the regex
 * @param word is the null terminated char array of word to match to
 * @param restriction is the restriction size for the tilde operator
 * @return 1 if it is a match, else 0 if it's not a match.
 */
int match(char *regex, char *word, int restriction);

/** Function to match for the tilde operator.
 * @param regex, is a null terminated char array of the regex
 * @param word is the null terminated char array of word to match to
 * @param restriction is the restriction size for the tilde operator
 * @return 1 if it is a match, else 0 if it's not a match.
 */
int match_tilde(char *regex, char *word, int restriction);

// Feel free to add more helper functions! Make sure they are well commented.

#endif
