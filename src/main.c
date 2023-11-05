#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>

char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// This table implements the mapping from 8-bit ascii value to 6-bit
int UNBASE64[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0-11
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 12-23
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 24-35
    -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 36-47
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -2, // 48-59
    -1,  0, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6, // 60-71
     7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, // 72-83
    19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 84-95
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, // 96-107
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, // 108-119
    49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120-131
  };

// -------------------------
// Function Signatures

void base64_encode(const char *in, const unsigned long in_len, char *out);
int base64_decode(const char *in, const unsigned long in_len, char *out);

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

int base64_decode(const char *in, const unsigned long in_len, char *out) {
    int in_index = 0;
    int out_index = 0;
    char first, second, third, fourth;

    assert(!(in_len & 0x03)); // input must be even multiple of 4

    while (in_index < in_len) {
        // Check if input is valid base64
	for (int i = 0; i < 4; i++) {
            if (((int)in[in_index + i] > 131) || UNBASE64[(int)in[in_index + i]] == -1) {
	        fprintf(stderr, "Invalid base64 char, cannot decode: %c\n", in[in_index + i]);
	        return -1;
	    }
	}

	// Extract all Bits and reconstruct original Bytes
	first   = UNBASE64[(int) in[in_index]];
	second = UNBASE64[(int) in[in_index+1]];
	third  = UNBASE64[(int) in[in_index+2]];
	fourth = UNBASE64[(int) in[in_index+3]];

	// Reconstruct First, Second and Third Byte
	out[out_index] = (first << 2) | ((second & 0x30) >> 4);
	out_index++;

	if (in[in_index + 2] != '=') {
	    out[out_index++] = ((second & 0xF) << 4) | ((third & 0x3C) >> 2);
	}

	if (in[in_index + 3] != '=') {
	    out[out_index++] = ((third & 0x3) << 6) | fourth;
	}
	
	in_index += 4;
    }

    out[out_index] = '\0';
    return 0;
}

// -------------------------
// TODO: Testing Helpers

int main() {
    while (!feof(stdin)) {
        char *input = readline("> ");
	unsigned long input_length = strlen(input);
	char output[128];

	base64_decode(input, input_length, output);
	printf("%s\n", output);

	free(input);
    }

    return 0;
}
