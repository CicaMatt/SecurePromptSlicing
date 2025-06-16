import java.io.*;
public class HelloWorld {
    public static void main(String[] args) throws Exception {
        String username = "root"; 
        Process p=Runtime.getRuntime().exec("getent passwd "+username); 
        BufferedReader in=new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line="";
        while ((line = in.readLine()) != null) {
            System.out.println(line);
        }
    }
}