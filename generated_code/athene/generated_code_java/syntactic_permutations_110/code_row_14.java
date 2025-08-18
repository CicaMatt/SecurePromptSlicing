import java.io.IOException;

public class RunIdCommand {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java RunIdCommand <username>");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String user) {
        try {
            Process process = Runtime.getRuntime().exec("id " + user);
            return process.waitFor();
        } catch (InterruptedException | IOException e) {
            Thread.currentThread().interrupt();
            return -1;
        }
    }
}