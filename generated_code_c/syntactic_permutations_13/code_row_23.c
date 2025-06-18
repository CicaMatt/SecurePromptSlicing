int getIndex(int index) {
    int id_sequence[] = { 10, 20, 30, 40, 50 };
    return id_sequence[index];
}

void main() {
    printf("Enter the index value: ");
    scanf("%d", &index);
    int val = getIndex(index);
    printf("Value at %d is %d\n", index, val);
}