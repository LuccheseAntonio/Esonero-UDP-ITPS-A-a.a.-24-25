#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "password_utils.h"

// Function to generate a numeric password
void generate_numeric(char *password, size_t length) {
    const char digits[] = "0123456789";
    size_t digits_length = strlen(digits);

    for (size_t i = 0; i < length; i++) {
        password[i] = digits[rand() % digits_length];
    }
    password[length] = '\0'; // End the string
}

// Function to generate an alphabetic password (lowercase letters only)
void generate_alpha(char *password, size_t length) {
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    size_t letters_length = strlen(letters);

    for (size_t i = 0; i < length; i++) {
        password[i] = letters[rand() % letters_length];
    }
    password[length] = '\0'; // End the string
}

// Function to generate a mixed password (lowercase letters and numbers)
void generate_mixed(char *password, size_t length) {
    const char mixed[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    size_t mixed_length = strlen(mixed);

    for (size_t i = 0; i < length; i++) {
        password[i] = mixed[rand() % mixed_length];
    }
    password[length] = '\0'; // End the string
}

// Function to generate a secure password (uppercase, lowercase, numbers, symbols)
void generate_secure(char *password, size_t length) {
    const char secure[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";
    size_t secure_length = strlen(secure);

    for (size_t i = 0; i < length; i++) {
        password[i] = secure[rand() % secure_length];
    }
    password[length] = '\0'; // End the string
}

// Function to generate a secure password without ambiguous characters
void generate_unambiguous(char *password, size_t length) {
    const char unambiguous[] = "abcdefghijklmnpqrtuvwxyzABCDEFGHJKLMNPQRTUVWXYZ23456789!#$%&()*+,-./:;<=>?@[]^_`{|}~";
    size_t unambiguous_length = strlen(unambiguous);

    for (size_t i = 0; i < length; i++) {
        password[i] = unambiguous[rand() % unambiguous_length];
    }
    password[length] = '\0'; // End the string
}
