#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// TODO: Add any other needed imports

// TODO: Add file constants for line and pattern length
#define PAT_LEN 101
#define LINE_LEN 502

// Copies a string (up to max length)
// Optionally converts the copied string to lowercase
// Params:
//  - copy_to:    The string/buffer to copy to
//  - copy_from:  The null-terminated string to copy from
//  - max_length: The max characters to copy over (including null terminator)
//  - lowercase:  Whether to convert to lowercase after copying
void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase);

// Prints all lines in a file that match the pattern
// Params:
//  - file:              the file to check for results
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_matches_in_file(FILE *file, char *pattern,
                           bool ignore_case, bool print_line_number);

// Loops through a list of files and prints matches to the pattern for each
// Params:
//  - num_files:         number of files in the list
//  - filename_list:     list of filenames to check
//  - pattern:           the pattern to look for in each line
//  - ignore_case:       whether to ignore case when using the pattern
//  - print_line_number: whether to print the line number for each matching line
void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number);

// Print the usage of the program
// Params:
//  - program_name: the name of the program being run (argv[0])
void usage(char *program_name);

// Main entry point of the function
// Parses the input into flags, pattern, and files
// Params:
//  - argc: The number of arguments provided
//  - argv: The list of arguments provided
// Returns the exit status
int main(int argc, char **argv);


// TODO: Fill in functions below

void copy_string(char *copy_to, char *copy_from, int max_length,
                 bool lowercase) {
    
    // Convert to lowercase
    if (lowercase)
    {
      tolower(*copy_to)
      tolower(*copy_from)
      strncpy(*copy_to, *copy_from, max_length);
    }
    else {
      strncpy(*copy_to, *copy_from, max_length);
   }
}
// ------------------------------------------------------------------
void print_matches_in_file(FILE *file, char *pattern,
                           bool ignore_case, bool print_line_number) {
    int lineNum = 1;
    
    // Check if the pointer exist
    // If pointer exist parse through file, else print "could not open"
    if (file != NULL)
    {
      char line[LINE_LEN];
      char pat[PAT_LEN];
      copy_string(pat, *pattern, PAT_LEN, ignore_case);
      
      // Parse through each line of the file
      while (fgets(line, LINE_LEN, file) != NULL)
      {
         
         // Check and find substring
         char *substring = strstr(line, *pattern)
         
         // If substring exist, then print the line
         if(substring != NULL)
         {
            if (print_line_number)
            {
               printf("(%i) %s", lineNum, line)
            }
            else {
               printf("%s", line)
            }
         }
         
         lineNum++;
      }
    }
    
    else {
      printf("Could not open file: %p", *file);
   }
}
// ---------------------------------------------------------------------

void print_all_matches(int num_files, char **filename_list, char *pattern,
                       bool ignore_case, bool print_line_number) {
   // Go through each file in the list
   for (i = 0; i < num_files; i++)
   {
     print_matches_in_file(filename_list[i], *pattern, ignore_case, print_line_number);
   }
}
// -------------------------------------------------------------------

void usage(char *program_name) {
    printf("Usage: %s [OPTIONS] pattern file...\n", program_name);
}

int main(int argc, char **argv) {
   
   // Print error if there is not enough parameters
   if (argc < 3)
   {
      fprintf(stderr, "%s\n", "Not enough arguments");
      exit(EXIT_FAILURE);
   }

   // Optional condition
   bool ignore_case;
   bool print_line_number;
   int startIndex = 0;

   // check if options are applied
    for (i = 0; i < 2; i++)
    {
      if (strncmp(argv[i], "-i\0") == 0)
      {
         ignore_case = true;
         startIndex += 1;
      }
      else if (strncmp(argv[i], "-n\0") == 0)
      {
         print_line_number = true;
         startIndex += 1;
      }
    }
    
    if( startIndex + 2 < argsc)
    {
      fprintf(stderr, "%s\n", "Not enough arguments");
      exit(EXIT_FAILURE);
    }
    
    // char pattern[] = arg[startIndex + 1];
    
    
}
