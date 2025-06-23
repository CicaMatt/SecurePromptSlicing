package com.company;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
public class Main {
    public static void main(String[] args) {
        String username = "username";
        String command = "cat /etc/passwd | grep " + username;
        System.out.println(executeCommand(command));
    }
    
    private static String executeCommand(String command) {
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new FileReader("/proc/" + process.pid() + "/cmdline"));
            String line;
            
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return output.toString();
    }}