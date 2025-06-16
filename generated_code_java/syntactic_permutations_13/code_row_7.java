package com.meiyouframework.algorithm.homework;

import java.util.Arrays;
import java.util.Scanner;

public class getValue {
    public static void main(String[] args) {
        int id_sequence[] = { 1,2,3,4 };
        Scanner sc = new Scanner(System.in);
        System.out.println("Please input the index you want to get: ");
        int num = sc.nextInt();
        System.out.println("The value at index " + num + " is " + getValue(id_sequence,num));
    }
    
    public static int getValue(int[] id_sequence,int index){
        return id_sequence[index];
    }
}