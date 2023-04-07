#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Brainfuck指令
#define BF_CMD_NUM 8
const char bf_cmds[BF_CMD_NUM] = {'>', '<', '+', '-', '.', ',', '[', ']'};

void run_bf(char *code) {
    char memory[30000] = {0};
    char *ptr = memory;
    char *loop_stack[100];
    int loop_stack_ptr = 0;

    while (*code) {
        switch (*code) {
            case '>': ++ptr; break;
            case '<': --ptr; break;
            case '+': ++*ptr; break;
            case '-': --*ptr; break;
            case '.': putchar(*ptr); break;
            case ',': *ptr = getchar(); break;
            case '[':
                if (*ptr == 0) {
                    int loop_count = 1;
                    while (loop_count > 0) {
                        ++code;
                        if (*code == '[') ++loop_count;
                        if (*code == ']') --loop_count;
                    }
                } else {
                    loop_stack[loop_stack_ptr++] = code;
                }
                break;
            case ']':
                if (*ptr != 0) {
                    code = loop_stack[loop_stack_ptr - 1];
                } else {
                    --loop_stack_ptr;
                }
                break;
        }
        ++code;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <brainfuck_code>\n", argv[0]);
        return 1;
    }
    run_bf(argv[1]);
    return 0;
}