import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserInformation <username>");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitCode = process.waitFor();
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}