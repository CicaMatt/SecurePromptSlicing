//This is the array of id numbers
int id_sequence[] = {1, 2, 3, 4, 5};

// This function takes in an index value and returns the value at that index in the array.
int getId(int index)
{
    // prompts user for index value
     printf("Enter index: ");
    scanf("%d", &index);
      // return value
    if (index < 0 || index >= sizeof(id_sequence) / sizeof(int))
        {
            printf("Invalid Index");
            return -1;
        }
        else{
            return id_sequence[index];
        }
}