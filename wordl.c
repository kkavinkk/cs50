#include <stdio.h>
#include <string.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

// Print he message "Enter guess:  ", read a string from stdin
// print colourized version of the guess followed by new line
// If the user did not guess the word right and hasnt mae 6 guesses try again
// If 6 guesses were made then print "Failed to guess the word:  <word>", new line
// then terminate the program
// If the user does guess the word correctlye then print "Finished in <n> guesses"


int main(int argc, char **argv) {
  if (argc != 2) {
      printf("Usage: %s word\n", argv[0]);
      return 1;
  }

  char *theWord = argv[1];
  int wordLen = strlen(theWord);
  int maxGuesses = 6;

  for (int attempt = 1; attempt <= maxGuesses; attempt++) {
      printf("Enter guess: ");
      fflush(stdout);

      char guess[20];
      if (fgets(guess, sizeof(guess), stdin) == NULL) {
          fprintf(stderr, "Error reading input.\n");
          return 1;
      }

      // Remove newline
      size_t guessLen = strlen(guess);
      if (guess[guessLen - 1] == '\n') {
          guess[guessLen - 1] = '\0';
          guessLen--;
      }

      // Arrays to mark greens and used letters
      int green[wordLen];
      int used[wordLen];
      int yellowCount[256] = {0}; // count of yellow letters printed
      int greenCount[256] = {0};  // count of green letters

      memset(green, 0, sizeof(green));
      memset(used, 0, sizeof(used));

      // First pass: detect GREEN matches
      for (int i = 0; i < wordLen; i++) {
          if (guess[i] == theWord[i]) {
              green[i] = 1;
              greenCount[(unsigned char)guess[i]]++;
          }
      }

      // Count total occurrences of each letter in the word
      int codeFreq[256] = {0};
      for (int i = 0; i < wordLen; i++) {
          codeFreq[(unsigned char)theWord[i]]++;
      }

      // Second pass: print with colors
      for (int i = 0; i < wordLen; i++) {
          char c = guess[i];
          if (green[i]) {
              setColour(GREEN);
              putchar(c);
          } else {
              // Count number of yellows + greens already printed for c
              int usedSoFar = yellowCount[(unsigned char)c] + greenCount[(unsigned char)c];
              if (codeFreq[(unsigned char)c] > usedSoFar) {
                  setColour(YELLOW);
                  yellowCount[(unsigned char)c]++;
              } else {
                  setColour(WHITE);
              }
              putchar(c);
          }
      }

      // End line and reset color
      setColour(WHITE);
      putchar('\n');

      // Check win
      if (strcmp(guess, theWord) == 0) {
          printf("Finished in %d guesses\n", attempt);
          return 0;
      }
  }

  printf("Failed to guess the word: %s\n", theWord);
  return 0;
}

