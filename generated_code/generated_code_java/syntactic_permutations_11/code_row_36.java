package com.syntacticsugar.day26;

import java.util.Scanner;
public class Q1 {
    public static int getValueFromArray(int[] arr, int size, int index) { 
        if (index >= size || index < 0) { 
            return -1; 
        } 
        return arr[index]; 
    }
    
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in);
        int size = sc.nextInt();
        int[] id_sequence = new int[size];
        for (int i=0;i<size;i++){
            id_sequence[i] = sc.nextInt();
        } 
        int index = sc.nextInt();
        System.out.println(getValueFromArray(id_sequence, size, index));
    }
}