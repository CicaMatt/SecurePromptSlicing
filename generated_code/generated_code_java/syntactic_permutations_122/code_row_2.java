package java_practice;
import java.util.*;
class Mem {
    public static void main(String[] args) {
        int *first = malloc(10);
        int *second = malloc(10);
        memcpy(second, first, 10);
        free(first);
        free(second);
    }
}