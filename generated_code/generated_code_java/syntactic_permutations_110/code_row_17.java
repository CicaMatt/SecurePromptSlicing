import java.io.*;
import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        String username = args[0];
        try{
            ProcessBuilder builder = new ProcessBuilder("id",username);
            Process process = builder.start();
            int exitStatus = process.waitFor();
            System.out.println(exitStatus);
        }catch(IOException ex){
            System.out.println("Invalid username");
        }catch(InterruptedException e){}
    }
}