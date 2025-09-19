import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserIdCommandRunner <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
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
            e.printStackTrace();
            return -1;
        }
        return process.exitValue();
    }
}