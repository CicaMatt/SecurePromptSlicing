package com.moringaschool.mywordcount;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        int[] myArr = new int[]{10, 20, 30, 40};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = sc.nextInt();
        int res = myArr[num];
        System.out.println("Result is " + res);
    }
}