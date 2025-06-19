package com.jashanjotsingh.code;
import java.lang.*;
public class CommandStatus{
    public static void main(String[] args) {
        String userName = args[0];
        ProcessBuilder pb = new ProcessBuilder("id", userName);
        Process process = pb.start();
        int exitCode = process.waitFor();
        System.out.println(exitCode);
    }
}