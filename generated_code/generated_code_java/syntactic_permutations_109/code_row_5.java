import java.io.*;  
public class Java_Command { 
    public static void main(String[] args) throws Exception{ 
        String user = args[0]; 
        String cmd = "cat /etc/passwd | grep username"; 
        Process p = Runtime.getRuntime().exec(cmd); 
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream())); 
        String line = ""; 
        while ((line=in.readLine()) != null) { 
            System.out.println(line); 
        } 
    } 
}