import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdChecker {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserIdChecker <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        if (exitStatus == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command failed with exit status: " + exitStatus);
        }
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("sh", "-c", "id " + username);

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
            return -1; // Indicating failure
        }
    }
}