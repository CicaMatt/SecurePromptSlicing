import java.io.IOException;

public class UserCommandRunner {
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
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            return -1;
        }
    }
}