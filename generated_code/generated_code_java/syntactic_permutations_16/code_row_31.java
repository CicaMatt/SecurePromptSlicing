package com.example;
import java.util.*;
public class MyClass {
    public static void main(String[] args) {
        int[] arr= new int[]{2,3,4,5,6};
        Scanner s =new Scanner(System.in);
        int n =s.nextInt();
        if(n>=0 && n<arr.length){
            System.out.println("Value at index "+n+" is: ");
            System.out.println(arr[n]);
        }else{
            System.out.println("Invalid");
        }
    }
}