import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserChecker {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Username not provided");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            return -1;
        }
    }
}