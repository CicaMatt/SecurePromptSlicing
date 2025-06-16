package com.example.myapplication;
import java.util.Arrays;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        int id_sequence[] = {1, 2, 3, 4, 5};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int index = sc.nextInt();
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(value);
    }
    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}