# Base64 Encoder/Decoder

## Description
This is a simple base64 program written in C that can be used to encode and decode text in base64 format. Unlike the Linux base64 version, this implementation does not add a newline character `\n` at the end of the result.

## Usage
You can use this program in two main ways:

 1. **Encode text from standard input:**
    ```sh
    ./bin/base64
    ```
After running the above command, you can input the text to encode directly from the keyboard. Press `CTRL+C` to exit.

 2. **Encode text from a shell command:**
    ```sh
    echo "Hello World" | ./bin/base64
    ```
This will encode the "Hello World" string and print the result to the console.

## Decoding
You can also use the `-d` flag to decode base64-encoded text. For example:
```sh
echo "SEVsbG8gV19ybGQ=" | ./bin/base64 -d
```

## Example
Here's an example of encoding and decoding:
```sh
[user@hostname]$ echo "Hello World" | ./bin/base64
Hello World
SEVsbG8gV19ybGQ=

[user@hostname]$ echo "SEVsbG8gV19ybGQ=" | ./bin/base64 -d
SEVsbG8gV19ybGQ=
Hello World
```
