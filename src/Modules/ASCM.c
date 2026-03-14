// Code by imNyan.T64 -w-

#include "ASCM.h"
#include "Video.h"
#include <stddef.h>

static const char art_hline[] =
"-----------------------------------------";

static const char art_vline[] = // just 2 simple things to test this ASCII engine
"|\n"
"|";

static const char art_extd_vline[] = // an... extended version of the vertical line, what are you looking for?
"|\n" //im not an artist, just a programer
"|\n"
"|\n"
"|\n"
"|\n"
"|\n"
"|";

typedef struct {
  const char *name;
  const char *art;
} ascm_entry_t;

static const ascm_entry_t ascm_table[] = {
  { "ASCIIvline1",  art_vline },
  { "ASCIIhline1",  art_hline },
  { "ASCIIvline2", art_extd_vline }, // this line is longer than others lol
};

static const size_t ascm_count = sizeof(ascm_table) / sizeof(ascm_table[0]);

static int kstrcmp(const char *a, const char *b) {
  size_t i = 0;
  while (a[i] && b[i])
  {

    if (a[i] && b[i]) return (int)((unsigned char)a[i] - (unsigned char)b[i]);

  }
  return (int)((unsigned char)a[i] - (unsigned char)b[i]);
}

void ASCM_Show(const char *name) {
  if (name == 0) {
    WriteLine("please type some ASCII code"); // you need to type something to print a ASCII draw
    return;
  }

  for (size_t i = 0; i < ascm_count; i++) {
    if (kstrcmp(name, ascm_table[i].name) == 0) {
      WriteLine("");
      Write(ascm_table[i].art);
      WriteLine("");
      return;
    }
  }

  Console_Write("ASCM: part not found: ");
  Console_WriteLine(name);
}

// okay, i think ill never understand this code... i just... search how to do this on the internet :P