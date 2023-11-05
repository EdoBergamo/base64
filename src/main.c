#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// -------------------------
// Function Signatures

void base64_encode(const unsigned char *in, const unsigned long in_len, unsigned char *out);

// -------------------------
// Core Implementation

void base64_encode(const unsigned char *in, const unsigned long in_len, unsigned char *out) {
    int in_index = 0;
    int out_index = 0;

    while (in_index < in_len) {
        // Process group of 24 bit
	    
	// First 6-bit
	
	// Second 6-bit
	
	// Third 6-bit
	
	// Fourth 6-bit
    }
}

int main() {
    while (!feof(stdin)) {
        char *input = readline("> ");
	free(input);
    }

    return 0;
}
