#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encrypt(char *text, int k) {
    int i;
    char ch;
    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ch = (ch - base + k) % 26 + base;
        }
        text[i] = ch;
    }
}

int main() {
    char text[100];
    int k;

    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the trailing newline character

    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);

    // Ensure the shift value is within the valid range
    if (k < 1 || k > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }

    encrypt(text, k);

    printf("Encrypted string: %s\n", text);

    return 0;
}
