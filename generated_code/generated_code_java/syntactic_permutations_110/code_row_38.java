java 
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("id " + username);
        int exitStatus = p.waitFor();
        if (exitStatus == 0)
            System.out.println("User " + username + " exists");
        else
            System.out.println("User " + username + " doesn't exist");
    }
}