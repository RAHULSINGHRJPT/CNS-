#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

void createMatrix(char key[]) {
    int flag[26] = {0}, x = 0, y = 0;

    for(int i = 0; i < strlen(key); i++) {
        if(key[i] != 'j' && flag[key[i] - 'a'] == 0) {
            matrix[x][y] = tolower(key[i]); // Convert to lowercase
            y++;
            if(y == SIZE) {
                x++;
                y = 0;
            }
            flag[key[i] - 'a'] = 1;
        }
    }

    for(int i = 0; i < 26; i++) {
        if(i != 'j' - 'a' && flag[i] == 0) {
            matrix[x][y] = (char)(i + 'a');
            y++;
            if(y == SIZE) {
                x++;
                y = 0;
            }
        }
    }
}

void search(char a, char b, int arr[]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(matrix[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if(matrix[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

void encrypt(char str[]) {
    char encrypted[strlen(str)];
    int arr[4];

    for(int i = 0; i < strlen(str); i += 2) {
        search(tolower(str[i]), tolower(str[i + 1]), arr);
        if(arr[0] == arr[2]) {
            encrypted[i] = matrix[arr[0]][(arr[1] + 1) % SIZE];
            encrypted[i + 1] = matrix[arr[0]][(arr[3] + 1) % SIZE];
        }
        else if(arr[1] == arr[3]) {
            encrypted[i] = matrix[(arr[0] + 1) % SIZE][arr[1]];
            encrypted[i + 1] = matrix[(arr[2] + 1) % SIZE][arr[1]];
        }
        else {
            encrypted[i] = matrix[arr[0]][arr[3]];
            encrypted[i + 1] = matrix[arr[2]][arr[1]];
        }
    }
    strcpy(str, encrypted); // Copy encrypted string back to original string
}

void decrypt(char str[]) {
    char decrypted[strlen(str)];
    int arr[4];

    for(int i = 0; i < strlen(str); i += 2) {
        search(tolower(str[i]), tolower(str[i + 1]), arr);
        if(arr[0] == arr[2]) {
            decrypted[i] = matrix[arr[0]][(arr[1] - 1 + SIZE) % SIZE];
            decrypted[i + 1] = matrix[arr[0]][(arr[3] - 1 + SIZE) % SIZE];
        }
        else if(arr[1] == arr[3]) {
            decrypted[i] = matrix[(arr[0] - 1 + SIZE) % SIZE][arr[1]];
            decrypted[i + 1] = matrix[(arr[2] - 1 + SIZE) % SIZE][arr[1]];
        }
        else {
            decrypted[i] = matrix[arr[0]][arr[3]];
            decrypted[i + 1] = matrix[arr[2]][arr[1]];
        }
    }
    strcpy(str, decrypted); // Copy decrypted string back to original string
}

int main() {
    char key[SIZE * SIZE];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character if present
    createMatrix(key);

    char str[100];
    printf("Enter the message to be encrypted: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character if present
    encrypt(str);
    printf("Encrypted message: %s\n", str);

    decrypt(str);
    printf("Decrypted message: %s\n", str);

 return 0;
}