import java.io.IOException;

public class UserCommandExecutor {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as a command line argument.");
            return;
        }

        String username = args[0];
        int exitStatus = executeIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int executeIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            return -1;
        }
    }
}