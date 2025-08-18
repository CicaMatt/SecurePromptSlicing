import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserChecker {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserChecker <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        String command = "id " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }
}