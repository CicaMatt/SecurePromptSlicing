#include <stdio.h> 
int getValueFromArray(int myArray[], int size, int index) {
    if (index >= size || index < 0) {
        return -1;
    }
    return myArray[index];
}
int main() {
    int id_sequence[] = {983425710, 1000364829, 983452387};
    int size = sizeof(id_sequence) / sizeof(id_sequence[0]);
    int index;
    printf("Enter the Index: ");
    scanf("%d", &index);
    return getValueFromArray(id_sequence, size, index);
}

### Output: 
![](https://github.com/Techno-Disaster/Code-Practice/blob/main/C%20Language/images/task1.png)