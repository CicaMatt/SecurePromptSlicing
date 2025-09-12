import java.io.IOException;

public class UserIdChecker {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}