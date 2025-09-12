import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdCommand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdCommand <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runUserIdCommand(username);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    private static int runUserIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            return exitCode;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Non-zero status for failure
        }
    }
}