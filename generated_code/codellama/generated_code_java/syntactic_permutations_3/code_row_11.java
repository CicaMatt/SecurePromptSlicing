package com.test.demo;
public class CopyBytes {
    public static void main(String[] args) {
        char[] destination = new char[5];
        String source = "Hello";
        copyBytes(destination,source);
        System.out.println("The string copied to the buffer is : " + destination);
    }
    public static void copyBytes(char[] dest, String src) {
        int i = 0;
        while (i < src.length()) {
            dest[i] = src.charAt(i);
            i++;
        }
    }
}