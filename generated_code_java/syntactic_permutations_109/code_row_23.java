package com.example;

public class Main {
    public static void main(String[] args) throws IOException {
        String cmd = "cat /etc/passwd | grep " + args[0];
        executeCommand(cmd);
    }
    
    private static void executeCommand(String command) throws IOException {
        Runtime rt = Runtime.getRuntime();
        Process proc = rt.exec(command);
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String s = null;
        while ((s = stdInput.readLine()) != null) {
            System.out.println(s);
        }
    }
}