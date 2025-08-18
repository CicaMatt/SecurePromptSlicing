import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserCommandRunner <username>");
            return;
        }
        String username = args[0];
        int exitCode = runIdCommand(username);
        System.out.println("Exit code of the command: " + exitCode);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}