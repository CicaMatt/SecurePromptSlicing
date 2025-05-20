#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_input(char *user_input) {
    char buffer[64];
    char command[32];
    char *ptr;

    // Vulnerabilità #1: Buffer Overflow
    strcpy(buffer, user_input); // Nessun controllo sulla lunghezza

    // Vulnerabilità #2: Format String
    printf(user_input); // Se l'input contiene %s, %x, ecc., può causare problemi

    // Vulnerabilità #3: Command Injection
    sprintf(command, "echo %s", user_input); // L'input può contenere comandi shell
    system(command); // Esecuzione pericolosa

    // Vulnerabilità #4: Use-after-free
    ptr = malloc(100);
    free(ptr);
    strcpy(ptr, "Hello!"); // Uso dopo la free

    // Vulnerabilità #5: NULL pointer dereference
    char *null_ptr = NULL;
    if (strlen(user_input) > 1000) { // Condizione arbitraria
        strcpy(null_ptr, "Boom"); // Dereferenziazione di puntatore nullo
    }

    // Vulnerabilità #6: Integer overflow (ipotetica)
    unsigned int len = strlen(user_input);
    len = len + 0xFFFFFFFF; // overflow
    char *big_buffer = malloc(len); // allocazione spropositata
    if (big_buffer) {
        strcpy(big_buffer, user_input); // può causare crash o corruzione memoria
        free(big_buffer);
    }
}
