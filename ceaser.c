#include <ctype.h>
#include <stdio.h>

void encrypt(char text[], int key) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        // Check for valid characters.
        if (isalnum(ch)) {
            // Lowercase characters.
          
                ch = (ch - 'a' + key) % 26 + 'a';
            }
           
        // Adding encoded answer.
        text[i] = ch;
    }
    printf("Encrypted message: %s\n", text);
}

void decrypt(char text[], int key) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        // Check for valid characters.
        if (isalnum(ch)) {
            // Lowercase characters.
            
                ch = (ch - 'a' - key + 26) % 26 + 'a';
            }
           
        // Adding decoded answer.
        text[i] = ch;
    }
    printf("Decrypted message: %s\n", text);
}

int main() {
    char text[500];
    int key;

    // Taking user input.
    printf("Enter a message to encrypt: ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", &key);

    // Encrypt the message.
    encrypt(text, key);

    // Decrypt the message.
    decrypt(text, key);

    return 0;
}
