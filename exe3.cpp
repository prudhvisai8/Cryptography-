#include <stdio.h>
#include <string.h>

// 5x5 matrix to store the Playfair cipher table
char matrix[5][5];

// Function to create the Playfair cipher table from a keyword
void createTable(char *keyword) {
    char alphabet[] = "abcdefghiklmnopqrstuvwxyz";
    int i, j, k;

    // Copy the keyword into the matrix, ignoring duplicates
    for (i = 0; i < strlen(keyword); i++) {
        char c = keyword[i];
        if (c == 'j') c = 'i'; // Replace J with I
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == c) break;
            }
            if (k < 5) break;
        }
        if (j < 5 && k < 5) continue;
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == '\0') {
                    matrix[j][k] = c;
                    break;
                }
            }
            if (k < 5) break;
        }
    }

    // Fill in the remaining spaces with the alphabet
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == '\0') {
                for (k = 0; k < strlen(alphabet); k++) {
                    char c = alphabet[k];
                    if (c == 'j') c = 'i'; // Replace J with I
                    int found = 0;
                    for (int x = 0; x < 5; x++) {
                        for (int y = 0; y < 5; y++) {
                            if (matrix[x][y] == c) {
                                found = 1;
                                break;
                            }
                        }
                        if (found) break;
                    }
                    if (!found) {
                        matrix[i][j] = c;
                        break;
                    }
                }
            }
        }
    }
}

// Function to encrypt a pair of letters
void encrypt(char *plaintext, char *ciphertext) {
    int i;
    for (i = 0; i < strlen(plaintext); i += 2) {
        char c1 = plaintext[i];
        char c2 = plaintext[i + 1];

        int row1, col1, row2, col2;
        for (row1 = 0; row1 < 5; row1++) {
            for (col1 = 0; col1 < 5; col1++) {
                if (matrix[row1][col1] == c1) break;
            }
            if (col1 < 5) break;
        }
        for (row2 = 0; row2 < 5; row2++) {
            for (col2 = 0; col2 < 5; col2++) {
                if (matrix[row2][col2] == c2) break;
            }
            if (col2 < 5) break;
        }

        if (row1 == row2) { // Same row
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) { // Same column
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else { // Different row and column
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char keyword[] = "playfair";
    char plaintext[] = "hide";
    char ciphertext[] = "xxxx";

    createTable(keyword);
    encrypt(plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}