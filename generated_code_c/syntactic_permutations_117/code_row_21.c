#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    int main() {
        float a, b, c;
        char str_a[20], str_b[20], str_c[20];

        // generate three random floats
        srand(time(NULL));
        a = (float)(rand());
        b = (float)(rand());
        c = (float)(rand());

        // convert the floats to strings using function
        snprintf(str_a, sizeof str_a, "%.2f", a);
        snprintf(str_b, sizeof str_b, "%.2f", b);
        snprintf(str_c, sizeof str_c, "%.2f", c);
    }