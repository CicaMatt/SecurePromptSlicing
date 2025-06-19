int get_value(int my_array[], int size, int key){
    if (size > 0) {
        for (int i = 0; i < size; i++){
            if (my_array[i] == key) {
                return i;
            }
        }
    }
return -1;
}