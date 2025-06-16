import java.io.*;
public class Passwd{
public static void main(String[] args) throws Exception {
        String user = args[0];
        ProcessBuilder pb = new ProcessBuilder("cat", " /etc/passwd | grep " + user);
        Process proc = pb.start(); 
        BufferedReader in = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String line;
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}