#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// -------------------------
// Function Signatures

void base64_encode();

int main() {
    while (!feof(stdin)) {
        char *input = readline("> ");
	free(input);
    }

    return 0;
}
