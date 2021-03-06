// Copyright 2020

// Import header files
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Add file constants for line and pattern length
#define PAT_LEN 101
#define LINE_LEN 502

// Print the usage of the program
// Params:
//  - program_name: the name of the program being run (argv[0])
void usage(char *program_name);

// Loops through a list of files and prints matches to the pattern for each
// Params:
//  - num_files:         number of files in the list
//  - filename_list:     list of filenames to check
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number);

// Main entry point of the function
// Parses the input into flags, pattern, and files
// Params:
//  - argc: The number of arguments provided
//  - argv: The list of arguments provided
// Returns the exit status
int main(int argc, char **argv);

// Main entry point of the function
int main(int argc, char **argv) {
  // Print error if there is not enough parameters
  if (argc < 3) {
    usage(argv[0]);
    fprintf(stderr, "%s\n", "Not enough arguments");
    exit(EXIT_FAILURE);
  }

  // Optional condition
  bool ignore_case;
  bool print_line_number;
  int startIndex = 0;

  // Check if options are passed
  for (int i = 1; i < 3; i++) {
    if (strncmp(argv[i], "-i\0", 3) == 0) {
      ignore_case = true;
      startIndex += 1;
    } else if (strncmp(argv[i], "-n\0", 3) == 0) {
      print_line_number = true;
      startIndex += 1;
    }
  }

  // Check if there is enough parameters
  if (startIndex + 3 > argc) {
    usage(argv[0]);
    fprintf(stderr, "%s\n", "Not enough arguments");
    exit(EXIT_FAILURE);
  }

  // Get parameters
  int fileIndex = startIndex + 2;
  char *pattern = argv[startIndex + 1];
  int num_files = argc - fileIndex;

  // Call print_all_matches
  print_all_matches(num_files, &argv[fileIndex], pattern,
                    ignore_case, print_line_number);

  exit(EXIT_SUCCESS);
}


// Copies a string (up to max length)
// Optionally converts the copied string to lowercase
// Params:
//  - copy_to:    The string/buffer to copy to
//  - copy_from:  The null-terminated string to copy from
//  - max_length: The max characters to copy over (including null terminator)
//  - lowercase:  Whether to convert to lowercase after copying
void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase);

// Copies a string (up to max length)
void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase) {
  // Convert to lowercase
  if (lowercase) {
    for (int i = 0; i < max_length; i++) {
      copy_to[i] = tolower(copy_from[i]);
    }
  } else {
    strncpy(copy_to, copy_from, max_length);
  }
}


// Prints all lines in a file that match the pattern
// Params:
//  - file:              the file to check for results
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_matches_in_file(FILE *file, char *pattern,
                           bool ignore_case, bool print_line_number);

void print_matches_in_file(FILE *file, char *pattern,
                           bool ignore_case, bool print_line_number) {
  int lineNum = 1;

  // Check if the pointer exist
  // If pointer exist parse through file, else print "could not open"
  if (file != NULL) {
    // Copy pattern and change if ignore_case is true
    char pat[PAT_LEN];
    copy_string(pat, pattern, PAT_LEN, ignore_case);

    // Parse through each line of the file
    char line[LINE_LEN];
    while (fgets(line, LINE_LEN, file) != NULL) {
      // Copy current line and change if ignore_case is true
      char curLine[LINE_LEN];
      copy_string(curLine, line, LINE_LEN, ignore_case);

      // Create an check substring exist, then print the line if it does exist
      char *substring = strstr(curLine, pat);
      if (substring != NULL) {
        if (print_line_number) {
          printf("(%d) %s", lineNum, line);
        } else {
          printf("%s", line);
        }
      }
      lineNum++;
    }
  }
}

void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number) {
  // Go through each file in the list
  for (int i = 0; i < num_files; i++) {
    FILE *file = fopen(filename_list[i], "r");
    if (file == NULL) {
      fprintf(stderr, "Could not open file: %s\n", filename_list[i]);
    } else {
      printf("%s:\n", filename_list[i]);
      print_matches_in_file(file, pattern, ignore_case, print_line_number);
    }
  }
}

void usage(char *program_name) {
  printf("Usage: %s [OPTIONS] pattern file...\n", program_name);
}
