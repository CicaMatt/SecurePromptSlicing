package com.example;
import java.util.*;
public class AddOffset {
    public static void main(String[] args) {
        int i = Integer.parseInt(args[0]);
        System.out.println("The original value is "+i);
        int offset = 1000;
        int result = i + offset;
        System.out.println("The new value with offset applied is "+result);
    }
}