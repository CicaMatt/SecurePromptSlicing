package com.app;

import java.io.*;

public class HttpHelloPage {
    
    public static void main(String[] args) throws IOException {
        String input = readRequest();
        String username = extractUserName(input);
        writeResponse("Hello, " + username);
    }
    
    private static String readRequest() throws FileNotFoundException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        return reader.readLine();
    }
    
    private static String extractUserName(String input) {
        String[] parts = input.split(":");
        return parts[1];
    }
    
    private static void writeResponse(String response) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
        writer.write(response);
        writer.flush();
    }
}