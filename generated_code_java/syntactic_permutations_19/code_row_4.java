package com.javacodegeeks.snippets.enterprise;
import java.util.*;  
public class CommandLineArgs {  
    public static void main(String[] args) {  
        int value = Integer.parseInt(args[0]);  
        System.out.println(value + 1000);  
    }  
}