import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCommandExecutor {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserCommandExecutor <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        String command = "id " + username;
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            while (reader.readLine() != null) {} // Consume the output
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }
}