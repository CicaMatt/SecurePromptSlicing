import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CheckUserId {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java CheckUserId <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runCommand("id", username);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    private static int runCommand(String command, String argument) {
        ProcessBuilder processBuilder = new ProcessBuilder(command, argument);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            while ((line = errorReader.readLine()) != null) {
                System.err.println(line);
            }

            int exitValue = process.waitFor();
            return exitValue;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1; // Non-zero value indicating failure
        }
    }
}