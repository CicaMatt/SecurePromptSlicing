int* id_sequence[] = {4, 1, -3, 9, 0};

int getValue(int index){
    printf("Enter a valid index: ");
    scanf("%d", &index);
    return id_sequence[index];
}