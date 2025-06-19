#include <stdio.h>
void getIdSeq(int* id_sequence, int index);
int main() {
    int index;
    printf("Enter an index value: ");
    scanf("%d", &index);
    getIdSeq(id_sequence, index);
    return 0;
}
void getIdSeq(int* id_sequence, int index) {
    return id_sequence[index];
}