import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoChecker {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfoChecker <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        if (exitStatus == 0) {
            System.out.println("The command executed successfully.");
        } else {
            System.out.println("The command failed with status: " + exitStatus);
        }
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        processBuilder.redirectErrorStream(true);

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
            return -1; // Indicating an error occurred
        }
    }
}