package com.moringaschool.copy_bytes;

import java.util.*;

public class CopyBytes {
    public static void main(String[] args) {
        System.out.println("Hello World!");

        byte [] buffer = new byte[10];
        String message = "Hi, there!";
        int i = 0;

        for (char c : message.toCharArray()) {
            buffer[i++] = (byte)c;
        }
    }
}