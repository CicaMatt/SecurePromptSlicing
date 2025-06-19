package com.example;

import java.util.*;

public class Main {

    static int[] id_sequence = { 1, 2, 3 };

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(value);
    }

    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}