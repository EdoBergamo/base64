#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// -------------------------
// Function Signatures

void base64_encode(const char *in, const unsigned long in_len, char *out);
void base64_decode(const char *in, const unsigned long in_len, char *out);

// -------------------------
// Core Implementation

void base64_encode(const char *in, const unsigned long in_len, char *out) {
    int in_index = 0;
    int out_index = 0;

    while (in_index < in_len) {
        // Process group of 24 bit
	    
	// First 6-bit
	out[out_index] = BASE64[(in[in_index] & 0xFC) >> 2];
	out_index++;

	if ((in_index + 1) == in_len) {
	    // First Padding Case
	    out[out_index++] = BASE64[((in[in_index] & 0x3) << 4)];
	    out[out_index++] = '=';
	    out[out_index++] = '=';
	    break;
	}

	// Second 6-bit
	out[out_index] = BASE64[((in[in_index] & 0x3) << 4) | ((in[in_index+1] & 0xF0) >> 4)];
	out_index++;

	if ((in_index + 2) == in_len) {
	   // Second Padding Case
	   out[out_index++] = BASE64[((in[in_index + 1] & 0xF) << 2)];
	   out[out_index++] = '='; 
	   break;
	}
	
	// Third 6-bit
	out[out_index] = BASE64[((in[in_index+1] & 0xF) << 2) | ((in[in_index+2] & 0xC0) >> 6)];
	out_index++;

	// Fourth 6-bit
	out[out_index] = BASE64[in[in_index+2] & 0x3F];
	out_index++;

	in_index += 3;
    }

    out[out_index] = '\0';

    return;
}

void base64_decode(const char *in, const unsigned long in_len, char *out) {
    // TODO
}

// -------------------------
// TODO: Testing Helpers

int main() {
    while (!feof(stdin)) {
        char *input = readline("> ");
	unsigned long input_length = strlen(input);
	char output[128];

	base64_encode(input, input_length, output);
	printf("%s\n", output);

	free(input);
    }

    return 0;
}
