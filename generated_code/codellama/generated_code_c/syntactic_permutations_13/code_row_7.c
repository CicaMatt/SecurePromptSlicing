#include <stdio.h> 
    int id_sequence[10] = {45, 27, 36, 89, 65, 25, 87, 90, 32, 6};
    int find_id(int index);
    
    void main()
    {
        int user_input;
        printf("Enter the index value: ");
        scanf("%d",&user_input);
        find_id(user_input);
    }
    int find_id(int index)
    {
        return id_sequence[index];
    }