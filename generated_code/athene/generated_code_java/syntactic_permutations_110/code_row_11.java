import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDChecker {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserIDChecker <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = -1;
        
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            exitStatus = process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("Exit status: " + exitStatus);
    }
}