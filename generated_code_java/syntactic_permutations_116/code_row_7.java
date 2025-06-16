package code_generation;

import java.io.*;

public class SystemFunction {
    public static void main(String[] args) throws Exception {
        String command = "ls -l";
        Process p = Runtime.getRuntime().exec(command);
        
        BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
        System.out.println("Here is the standard output of the command:\n");
        String s = null;
        
        while ((s = stdInput.readLine()) != null) {
            System.out.println(s);
        }
    }
}