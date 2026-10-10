#define _DEFAULT_SOURCE

#include "../test.h"
#include "group_1_copy.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

/* 
    Будем использовать CWE120 - переполнение буфера
    Т.к strcpy не имеет параметра, передающего размер буфера
    CWE125 - отстутствие нуля-сепоратора
    CWE476 - отсутствие проверки NULL
    OVERLAP CWEundefind
*/

jmp_buf jump_buffer;
void sigsegv_handler(int sig) {
    (void)sig;
    longjmp(jump_buffer,1);
}

bool testStrCpy(void){
    int passed = 0, total = 3;
    void (*old_handler)(int) = NULL;
    // ===== ТЕСТ 1: Переполнение буфера (CWE-120) =====
    volatile cpy_test ctx;
    strcpy((char*)ctx.dest, "1234");
    ctx.guard = 0xDEADBEEF;
    strcpy((char*)ctx.dest, "ОЧЕНЬ_ДЛИЕННАЯ_СТРОКА_ОЧЕНЬ");
    if(ctx.guard == 0xDEADBEEF) printf("TEST 1 FAILED: Guard unchanged. Overflow did not reach guard.\n");
    if(ctx.guard != 0xDEADBEEF) printf("TEST 1 PASSED: Buffer overflow detected (guard = 0x%X)\n", ctx.guard);
    if(ctx.guard != 0xDEADBEEF) passed ++;
        
    
    // ===== ТЕСТ 2: OVERLAP allowed =====
    char str[20] = "HELLO WORLD TEST";
    strcpy(str+2, str);
    printf("TEST 2 PASSED: Overlap allowed (result = '%s')\n", str);
    passed++;
    

    // ===== ТЕСТ 3: NULL POINTER =====
    char dest[20];
    ASSERT_CRASH(strcpy(dest,NULL));
    printf("TEST 3 PASSED: Crash (SIGSEGV) successfully detected on NULL pointer\n");
    passed++;
    test_failed:

    printf("\n strcpy: %d/%d tests passed\n", passed, total);
    return (passed == total);
}


