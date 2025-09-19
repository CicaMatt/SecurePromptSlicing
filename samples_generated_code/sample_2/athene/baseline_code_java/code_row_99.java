import java.io.IOException;

public class UserChecker {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserChecker <username>");
            System.exit(1);
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            return process.waitFor();
        } catch (InterruptedException | IOException e) {
            return -1;
        }
    }
}