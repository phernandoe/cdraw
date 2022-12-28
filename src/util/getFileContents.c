#include <stdio.h>
#include <stdlib.h>
#include "getFileContents.h"

char *getFileContents(char *filePath)
{
  FILE *infile = fopen(filePath, "r");
  if (infile == NULL)
    return NULL;

  /* Get the number of bytes */
  fseek(infile, 0L, SEEK_END);
  long numbytes = ftell(infile);

  /* reset the file position indicator to
  the beginning of the file */
  fseek(infile, 0L, SEEK_SET);

  /* grab sufficient memory for the
  buffer to hold the text */
  char *buffer = (char *)calloc(numbytes, sizeof(char));

  /* memory error */
  if (buffer == NULL) return NULL;

  /* copy all the text into the buffer */
  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);

  return buffer;
}