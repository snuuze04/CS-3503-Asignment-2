#include <stdlib.h>
#include <string.h>


void oct_to_bin(const char *oct, char *out) {
    int pos = 0;

    for (int i = 0; oct[i] != '\0'; i++) {
        char c = oct[i];

        if (c < '0' || c > '7') {
            continue;
        }

        int octal_digit = c - '0';

        // Build binary from octal digit using bit shifts
        // Example: 7 -> "111"
        out[pos++] = (octal_digit >> 2) & 1 ? '1' : '0';
        out[pos++] = (octal_digit >> 1) & 1 ? '1' : '0';
        out[pos++] = (octal_digit >> 0) & 1 ? '1' : '0';
    }

    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out) {
    if (strcmp(oct, "0") == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }

    char bin[100];
    oct_to_bin(oct, bin);

    int bin_len = strlen(bin);

    int zeros = (4 - (bin_len % 4)) % 4;

    char zeros_added[132];
    int pos = 0;

    for (int i = 0; i < zeros; i++) {
        zeros_added[pos++] = '0';
    }

    for (int i = 0; i < bin_len; i++) {
        zeros_added[pos++] = bin[i];
    }
    zeros_added[pos] = '\0';

    int zeros_len = strlen(zeros_added);
    pos = 0;
    int leading_zeros = 1;

    for (int i = 0; i < zeros_len; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = val << 1;
            if (zeros_added[i + j] == '1') {
                val |= 1;
            }
        }

        if (leading_zeros && val == 0) {
            continue;
        }
        leading_zeros = 0;

        if (val < 10) {
            out[pos++] = '0' + val;
        } else {
            out[pos++] = 'A' + (val - 10);
        }
    }

    if (pos == 0) {
        out[pos++] = '\0';
    }

    out[pos] = '\0';
}

void hex_to_bin(const char *hex, char *out) {
    int pos = 0;

    for (int i = 0; hex[i] != '\0'; i++) {
        char c = hex[i];

        int hex_digit = 0;

        if (c >= '0' && c <= '9') {
            hex_digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            hex_digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            hex_digit = c - 'a' + 10;
        }

        out[pos++] = (hex_digit >> 3) & 1 ? '1' : '0';
        out[pos++] = (hex_digit >> 2) & 1 ? '1' : '0';
        out[pos++] = (hex_digit >> 1) & 1 ? '1' : '0';
        out[pos++] = (hex_digit >> 0) & 1 ? '1' : '0';
    }

    out[pos] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) {
    int32_t val;
    int pos = 0;

    if (n >= 0) {
        val = n;
        out[pos++] = '0';
    } else {
        val = abs(n);
        out[pos++] = '1';
    }

    for (int i = 30; i >= 0; i--) {
        out[pos++] = (val >> i) & 1 ? '1' : '0';
    }

    out[pos] = '\0';
}

void to_ones_complement(int32_t n, char *out) {
    uint32_t val;
    int pos = 0;

    if (n >= 0) {
        val = (uint32_t)n;
    } else {
        val = (uint32_t)(-n);
        val = ~val;
    }

    for (int i = 31; i >= 0; i--) {
        out[pos++] = (val >> i) & 1 ? '1' : '0';
    }

    out[pos] = '\0';
}

void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t)n;
    int pos = 0;

    for (int i = 31; i >= 0; i--) {
        out[pos++] = (val >> i) & 1 ? '1' : '0';
    }

    out[pos] = '\0';
}