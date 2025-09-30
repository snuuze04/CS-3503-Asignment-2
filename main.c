#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main() {
    FILE *file = fopen("/Users/shannonjones/Desktop/Assignment 2 ARCH/a2_test.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open a2_test.txt\n");
        return 1;
    }

    char line[256];
    int test_num = 1;
    int total = 0;
    int passed = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '#' || line[0] == '\0') {
            continue;
        }

        char func[32];
        char input[128];
        char expected[128];
        char result[128];

        if (sscanf(line, "%s %s %s", func, input, expected) != 3) {
            continue;
        }

        total++;

        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(input, result);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(input, result);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(input, result);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            to_sign_magnitude(atoi(input), result);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            to_ones_complement(atoi(input), result);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            to_twos_complement(atoi(input), result);
        } else {
            continue;
        }

        if (strcmp(result, expected) == 0) {
            printf("Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, func, input, expected, result);
            passed++;
        } else {
            printf("Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, func, input, expected, result);
        }

        test_num++;
    }

    fclose(file);

    printf("Summary: %d/%d tests passed\n", passed, total);

    return 0;
}