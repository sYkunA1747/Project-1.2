#ifndef GROUP_1_COPY_H
#define GROUP_1_COPY_H

typedef struct {
    char dest[8];
    int guard;
} __attribute__((packed)) cpy_test;

typedef struct {

} LCPY_TEST;

typedef struct {} NCPY_TEST;

extern jmp_buf jump_buffer;
extern void sigsegv_handler(int sig);

#define ASSERT_CRASH(statement) do {\
    void(*old_h)(int) = signal(SIGSEGV, sigsegv_handler);\
    if(setjmp(jump_buffer) != 0) { \
        signal(SIGSEGV, old_h); \
        break;\
    }\
    statement; \
    printf("FAILED: Expected crash did not happen!\n");\
    signal(SIGSEGV, old_h);\
    goto test_failed;\
} while(0)

#endif