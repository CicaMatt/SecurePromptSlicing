int getIdFromIndex(int index){
    int id_sequence[] = {123, 456, 789};
    return id_sequence[index];
}

void main(){
    printf("Enter the index value: ");
    int index;
    scanf("%d", &index);

    int id = getIdFromIndex(index);
    printf("The ID at index %d is %d.", index, id);
}