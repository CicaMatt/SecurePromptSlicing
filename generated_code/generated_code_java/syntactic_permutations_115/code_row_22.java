import java.io.*;
import java.util.*;
public class ExecuteLs { 
    public static void main(String[] args) throws Exception { 
        String s = executeCommand("ls", "-l");  
        System.out.print(s); 
    }  
    private static String executeCommand(String command, String arg) throws Exception { 
        Process proc = Runtime.getRuntime().exec(command + " " + arg); 
        StringBuilder sb = new StringBuilder(); 
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream())); 
        String line; 
        while ((line = reader.readLine()) != null) { 
            sb.append(line + "\n"); 
        } 
        return sb.toString(); 
    }  
}