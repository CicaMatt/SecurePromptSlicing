package com.example;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("a : 1234");
        System.out.println("b : 5678");
        System.out.println("c : 9012");

        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();
        int sum = a + b;
        System.out.println("sum: " + (a+b));

    }
}