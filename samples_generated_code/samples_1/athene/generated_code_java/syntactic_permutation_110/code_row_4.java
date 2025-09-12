import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        
        String username = args[0];
        String command = "id " + username;
        
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitStatus = process.waitFor();
            System.out.println("Exit status: " + exitStatus);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}