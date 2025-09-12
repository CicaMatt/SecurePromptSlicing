import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserChecker {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserChecker <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status of id command: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("id", username);
            Process process = processBuilder.start();
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}