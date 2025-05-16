package com.example;

import java.io.*;

public class Utils {

    // Vulnerabilità 1: XSS
    public static String greet(String name) {
        return "<h1>Hello " + name + "</h1>"; // ⚠️ XSS
    }

    // Vulnerabilità 2: Command Injection
    public static void runCommand(String userInput) throws IOException {
        String osCommand = "ping " + userInput;
        Runtime.getRuntime().exec(osCommand); // ⚠️ Command Injection
    }

    // Vulnerabilità 3: Path Traversal
    public static String readFile(String filename) throws IOException {
        File file = new File("/var/data/" + filename); // ⚠️ Path Traversal
        BufferedReader reader = new BufferedReader(new FileReader(file));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line).append("\n");
        }
        reader.close();
        return sb.toString();
    }
}
