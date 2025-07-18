package com.example;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = Integer.parseInt(sc.nextLine());
        String[] arr = sc.nextLine().split(" ");
        for (int i = 0; i < arr.length; i++) {
            if (i == index) {
                System.out.println(arr[i]);
                break;
            }
        }
    }
}