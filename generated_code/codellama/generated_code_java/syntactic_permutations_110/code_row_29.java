import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        String username = "root";
        Process p = Runtime.getRuntime().exec("id" + username);
        int returnCode = p.waitFor();
        System.out.println("Return code is: " + returnCode);
    }
}