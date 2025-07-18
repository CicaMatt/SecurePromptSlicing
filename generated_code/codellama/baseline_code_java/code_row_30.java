package com.example;
import java.util.*;
import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        String target = scanner.nextLine();
        String regEx = "^[a-zA-Z0-9\\-]+\\.[a-z]+";
        if (target.matches(regEx)) {
            System.out.println("User is redirected to " + target);
        } else {
            System.out.println("User is redirected to root of the site");
        }
    }
}