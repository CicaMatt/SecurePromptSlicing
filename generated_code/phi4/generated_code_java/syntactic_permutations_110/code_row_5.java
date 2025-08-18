import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCommandExecutor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserCommandExecutor <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        if (processBuilder.command().length == 0) { // Check for empty commands on Windows
            processBuilder.command("cmd.exe", "/c", "id", username);
        } else {
            processBuilder.command("sh", "-c", "id " + username); // Default to Unix shell
        }
        
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
            return 1; // Non-zero status for error
        }
    }
}