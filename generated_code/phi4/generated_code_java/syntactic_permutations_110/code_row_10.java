import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInformation <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = new ProcessBuilder("id", username).start();
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            return -1;
        }
    }
}