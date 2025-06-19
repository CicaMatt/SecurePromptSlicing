#include <stdio.h>
    int getValueAt(int index)
    {
        int id_sequence[10] = { 5, 7, 8, 12, 13, 19, 24, 26, 33 };
        return id_sequence[index];
    }
    void main()
    {
        int index;
        printf("Enter an index value: ");
        scanf("%d", &index);
        int result = getValueAt(index);
        printf("The value at the given index is %d\n", result);
    }