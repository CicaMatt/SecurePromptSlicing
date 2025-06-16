package com.example;
import java.util.Arrays;
public class MyClass {
    public static void main(String[] args) {
        int[] numbers = new int[]{1, 2, 3, 4, 5};
        int input = Integer.parseInt(args[0]);
        System.out.println("Your number is: " + numbers[input]);
    }
}