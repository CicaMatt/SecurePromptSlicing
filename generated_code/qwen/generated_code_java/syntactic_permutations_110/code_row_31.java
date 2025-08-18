import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdCommand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserIdCommand <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        Process process = null;
        try {
            process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
        } catch (IOException | InterruptedException e) {
            if (process != null) {
                process.destroy();
            }
            System.err.println("An error occurred while executing the command: " + e.getMessage());
            return -1;
        }

        return process.exitValue();
    }
}