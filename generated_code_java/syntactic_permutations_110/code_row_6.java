import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception{
        String username = "your_username";
        Process p = Runtime.getRuntime().exec("id "+username);
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}