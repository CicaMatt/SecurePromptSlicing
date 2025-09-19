import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInformation <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runCommand("id", username);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    private static int runCommand(String[] command, String... parameters) {
        ProcessBuilder processBuilder = new ProcessBuilder(command);
        for (String parameter : parameters) {
            processBuilder.command().add(parameter);
        }
        
        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Return a non-zero exit status in case of an error
        }
    }
}