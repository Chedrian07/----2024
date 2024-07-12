#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define KEY_FILE "key.dat"
#define MAX_KEY_SIZE 256

void generate_fibonacci_key(uint8_t *key, int size) {
    key[0] = 1;
    key[1] = 1;
    for (int i = 2; i < size; ++i) {
        key[i] = (key[i-1] + key[i-2]) % 256;
    }
}

void encrypt_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        return;
    }

    uint8_t key[MAX_KEY_SIZE];
    generate_fibonacci_key(key, MAX_KEY_SIZE);

    FILE *key_file = fopen(KEY_FILE, "wb");
    if (!key_file) {
        perror("Failed to open key file");
        fclose(input_file);
        fclose(output_file);
        return;
    }
    fwrite(key, 1, MAX_KEY_SIZE, key_file);
    fclose(key_file);

    int c;
    int i = 0;
    while ((c = fgetc(input_file)) != EOF) {
        uint8_t encrypted_byte = c ^ key[i % MAX_KEY_SIZE];
        fputc(encrypted_byte, output_file);
        i++;
    }

    fclose(input_file);
    fclose(output_file);
}

void decrypt_file(const char *input_filename, const char *output_filename, const char *key_filename) {
    FILE *key_file = fopen(key_filename, "rb");
    if (!key_file) {
        perror("Failed to open key file");
        return;
    }

    uint8_t key[MAX_KEY_SIZE];
    fread(key, 1, MAX_KEY_SIZE, key_file);
    fclose(key_file);

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Failed to open input file");
        return;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        fclose(input_file);
        return;
    }

    int c;
    int i = 0;
    while ((c = fgetc(input_file)) != EOF) {
        uint8_t decrypted_byte = c ^ key[i % MAX_KEY_SIZE];
        fputc(decrypted_byte, output_file);
        i++;
    }

    fclose(input_file);
    fclose(output_file);
}

int main() {
    char choice;
    char input_filename[256];
    char output_filename[256];
    char key_filename[256];

    printf("Would you like to (e)ncrypt or (d)ecrypt a file? ");
    scanf(" %c", &choice);

    if (choice == 'e') {
        printf("Enter the name of the file to encrypt: ");
        scanf("%s", input_filename);
        printf("Enter the name of the output encrypted file: ");
        scanf("%s", output_filename);
        encrypt_file(input_filename, output_filename);
    } else if (choice == 'd') {
        printf("Enter the name of the file to decrypt: ");
        scanf("%s", input_filename);
        printf("Enter the name of the output decrypted file: ");
        scanf("%s", output_filename);
        printf("Enter the key file path: ");
        scanf("%s", key_filename);
        decrypt_file(input_filename, output_filename, key_filename);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
