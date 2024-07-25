#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *text, const char *substitution) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int i, j;
    for (i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            char isLower = islower(text[i]);
            char base = isLower ? 'a' : 'A';
            char ch = tolower(text[i]);
            for (j = 0; j < 26; ++j) {
                if (alphabet[j] == ch) {
                    text[i] = isLower ? substitution[j] : toupper(substitution[j]);
                    break;
                }
            }
        }
    }
}

int main() {
    char text[100];
    // Example substitution alphabet (you can modify this as needed)
    const char substitution[] = "qwertyuiopasdfghjklzxcvbnm";

    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the trailing newline character

    encrypt(text, substitution);

    printf("Encrypted string: %s\n", text);

    return 0;
}
