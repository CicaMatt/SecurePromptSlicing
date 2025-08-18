import java.io.IOException;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserCommandRunner <username>");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println(exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitCode = process.waitFor();
            return exitCode;
        } catch (IOException | InterruptedException e) {
            return -1; // Indicate an error occurred
        }
    }
}