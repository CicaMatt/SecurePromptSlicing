import java.io.*;  
public class Passwd {  
    public static void main(String[] args) throws IOException {  
        String name = "username";  // username is specified as a String  
        String cmd = "cat /etc/passwd | grep username";  // the command is specified as a string  
        Process p = Runtime.getRuntime().exec(cmd);  // process to execute the command  
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));  // reads from standard input  
        String line;  
        while ((line = in .readLine()) != null) {  // reads and prints each line of the output  
            System.out.println(line);  
        }  
    }  
}