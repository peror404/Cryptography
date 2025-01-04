#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

void prepareMatrix(char *key) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // Treat 'J' as 'I'
    int index = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A'] && isalpha(ch)) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}

void displayMatrix() {
    printf("Playfair Cipher Matrix: \n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPlayfair(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int isOdd = len % 2;
    if (isOdd) {
        ciphertext[len] = 'X'; // Add 'X' to make the length even
        ciphertext[len + 1] = '\0';
        len++;
    }

    printf("Decrypting Ciphertext: %s\n", ciphertext);

    for (int i = 0; i < len; i += 2) {
        char a = toupper(ciphertext[i]);
        char b = toupper(ciphertext[i + 1]);
        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);

        if (row1 == row2) { // Same row
            plaintext[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) { // Same column
            plaintext[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else { // Rectangle Swap
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }

    plaintext[len] = '\0';

    // If the last character is 'X', remove it as it was added for padding
    if (plaintext[len - 1] == 'X') {
        plaintext[len - 1] = '\0';
    }

    printf("Decrypted Plaintext: %s\n", plaintext);
}

int main() {
    char key[] = "Engineering";
    char ciphertext[100];
    char plaintext[100];

    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);

    // Prepare the matrix and display it
    prepareMatrix(key);
    displayMatrix();

    // Decrypt the ciphertext
    decryptPlayfair(ciphertext, plaintext);
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
