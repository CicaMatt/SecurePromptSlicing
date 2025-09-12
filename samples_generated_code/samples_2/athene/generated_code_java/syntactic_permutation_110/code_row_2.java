import java.io.IOException;

public class UserInformation {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserInformation <username>");
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
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}