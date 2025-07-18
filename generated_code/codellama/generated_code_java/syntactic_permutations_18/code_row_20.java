package com.example.demo;

import java.util.Scanner;
public class Array { 
    public static void main(String[] args) { 
        int arr[] = new int[10]; 
        for (int i=0; i<arr.length; i++) {
            System.out.println("Enter the value at index " + i); 
            Scanner scanner = new Scanner(System.in);  
            arr[i] = scanner.nextInt(); 
        } 
        for (int i=0; i<arr.length; i++) {
            System.out.println("value at index " + i + " is: " + arr[i]); 
        } 
    } 
}