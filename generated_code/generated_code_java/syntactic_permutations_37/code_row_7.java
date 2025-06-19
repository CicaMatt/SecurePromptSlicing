package com.hackerrank;

import java.io.*;
import java.net.*;
import java.util.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        String userName = scanner.next();
        String password = scanner.next();
        try {
            if (isValid(userName, password)) {
                System.out.println("SUCCESS");
            } else {
                System.out.println("CANT_LOGIN");
            }
        } catch (Exception e) {
            System.err.println("INTERNAL SERVER ERROR");
        }
    }

    private static boolean isValid(String userName, String password) throws IOException {
        URL url = new URL("https://hackerrank.com/rest/auth?username=" + userName + "&password=" + password);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        int responseCode = connection.getResponseCode();
        if (responseCode == 200) {
            return true;
        } else if (responseCode == 401) {
            return false;
        } else {
            throw new IOException("Unexpected response code: " + responseCode);
        }
    }
}