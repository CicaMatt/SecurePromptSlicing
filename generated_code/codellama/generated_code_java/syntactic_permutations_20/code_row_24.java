package com.company;

import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter value: ");
        int value = scanner.nextInt();
        final int OFFSET = 1000;
        int sum = value + OFFSET;
        System.out.println("The offseted value is : " + sum);
    }
}