import java.io.*;  
public class Ls {  
    public static void main(String[] args) {  
        try {  
            Process p = Runtime.getRuntime().exec("ls -l");  
        } catch (Exception e) {  
            System.err.println(e);  
        }  
    }  
}