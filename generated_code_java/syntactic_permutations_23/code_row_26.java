package com.davinci;

import java.util.*;

public class RandomIntegers {

    public static void main(String[] args) {
        int a = new Random().nextInt(9000);
        int b = new Random().nextInt(9000);
        int c = new Random().nextInt(9000);
        
        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        
        System.out.println("sum: " + (a+b+c));
    }
}