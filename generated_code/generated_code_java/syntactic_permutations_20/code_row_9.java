package com.example;
import java.util.Scanner;
public class AddOffset {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int offset = 1000;
        System.out.print("Enter the value to be added: ");
        int value = sc.nextInt();
        sc.close();
        int result = value + offset;
        System.out.println("Value after adding offset : " + result);
    }
}