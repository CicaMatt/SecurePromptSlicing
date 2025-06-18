void copy_message(char* destination, char* source, int number_of_bytes){
    for (int i = 0; i < number_of_bytes; ++i){
        destination[i] = source[i];
    }
}