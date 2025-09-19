import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CheckUser {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java CheckUser <username>");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        String command = "id " + username;
        try {
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}