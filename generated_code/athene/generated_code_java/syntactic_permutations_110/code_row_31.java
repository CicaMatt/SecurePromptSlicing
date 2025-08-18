import java.io.IOException;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserCommandRunner <username>");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process p = Runtime.getRuntime().exec("id " + username);
            return p.waitFor();
        } catch (InterruptedException | IOException e) {
            return -1;
        }
    }
}