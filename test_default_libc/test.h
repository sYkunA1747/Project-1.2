#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

//* GROUP 1: COPY
bool testStrCpy(void);
bool testStrNCpy(void);
bool testStrLCpy(void);


//* GROUP 2: CONCATENATION
bool testStrCat(void);
bool testStrNCat(void);
bool testStrLCat(void);


//* GROUP 3: LENGTH & COMPARE
bool testStrLen(void);
bool testStrCmp(void);
bool testStrNCmp(void);


//* GROUP 4: SEARCH
bool testStrChr(void);
bool testStrStr(void);


//* GROUP 5: TOKENIZE
bool testStrTok(void);


#endif