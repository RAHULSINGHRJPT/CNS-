
// Function to encrypt a message using a monoalphabetic cipher
#include<ctype.h>
#include<string.h>
#include<stdio.h>
void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = key[plaintext[i] - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

// Function to decrypt a ciphertext using a monoalphabetic cipher
void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = 'A' + strchr(key, ciphertext[i]) - key;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[] = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char ciphertext[strlen(plaintext) + 1];
    char decrypted[strlen(plaintext) + 1];

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted message: %s\n", decrypted);

  return 0;
}