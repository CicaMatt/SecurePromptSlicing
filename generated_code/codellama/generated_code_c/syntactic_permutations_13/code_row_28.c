#include <stdio.h>

    int id_sequence[10] = { 23, 56, -78, 90, -45, 0, 234, -1234, 567, 890 };

    void print(int value) { printf("%d\n", value); }

    int main() {
        int index;
        scanf("%d", &index);
        print(id_sequence[index]);
        return 0;
    }