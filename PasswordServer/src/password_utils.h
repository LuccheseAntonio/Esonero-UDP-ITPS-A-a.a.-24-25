#ifndef PASSWORD_UTILS_H
#define PASSWORD_UTILS_H

// Function to generate a numeric password
void generate_numeric(char *password, size_t length);

// Function to generate an alphabetic password (lowercase letters only)
void generate_alpha(char *password, size_t length);

// Funzione per generare una password mista (lettere minuscole e numeri)
void generate_mixed(char *password, size_t length);

// Function to generate a mixed password (lowercase letters and numbers)
void generate_secure(char *password, size_t length);

// Function to generate a secure password without ambiguous characters
void generate_unambiguous(char *password, size_t length);

#endif // PASSWORD_UTILS_H
