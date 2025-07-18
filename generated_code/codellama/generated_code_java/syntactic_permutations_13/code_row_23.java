package com.example;
import java.util.*;
public class App {
    public static void main(String[] args) {
        int[] id_sequence = {1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int indexValue = scanner.nextInt();
        int result = getIndexValue(id_sequence, indexValue);
        System.out.println(result);
    }
    public static int getIndexValue(int[] id_sequence, int index) {
        return id_sequence[index];
    }
}