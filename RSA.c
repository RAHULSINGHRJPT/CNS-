#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>

// Function to create RSA structure from a public key file
RSA *createRSAWithFilename(char *filename, int public) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }

    RSA *rsa = RSA_new();
    if (public) {
        rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
    } else {
        rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
    }

    fclose(fp);
    return rsa;
}

// Function to perform RSA encryption
int public_encrypt(unsigned char *data, int data_len, char *key_filename, unsigned char *encrypted) {
    RSA *rsa = createRSAWithFilename(key_filename, 1);
    int result = RSA_public_encrypt(data_len, data, encrypted, rsa, RSA_PKCS1_PADDING);
    RSA_free(rsa);
    return result;
}

// Function to perform RSA decryption
int private_decrypt(unsigned char *enc_data, int data_len, char *key_filename, unsigned char *decrypted) {
    RSA *rsa = createRSAWithFilename(key_filename, 0);
    int result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, RSA_PKCS1_PADDING);
    RSA_free(rsa);
    return result;
}

int main() {
    // Message to be encrypted
    unsigned char message[] = "Hello, User B!";
    unsigned char encrypted[256];
    unsigned char decrypted[256];

    char publicKeyFilename[] = "public_key.pem";
    char privateKeyFilename[] = "private_key.pem";

    // Encrypt the message
    int encrypted_length = public_encrypt(message, strlen((char *)message), publicKeyFilename, encrypted);
    if (encrypted_length == -1) {
        fprintf(stderr, "Public Encrypt failed\n");
        exit(0);
    }

    printf("Encrypted message: ");
    for (int i = 0; i < encrypted_length; i++) {
        printf("%x", encrypted[i]);
    }
    printf("\n");

    // Decrypt the message
    int decrypted_length = private_decrypt(encrypted, encrypted_length, privateKeyFilename, decrypted);
    if (decrypted_length == -1) {
        fprintf(stderr, "Private Decrypt failed\n");
        exit(0);
    }

    // Add null terminator to decrypted message
    decrypted[decrypted_length] = '\0';

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
