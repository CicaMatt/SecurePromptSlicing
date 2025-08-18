import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserSearch {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserSearch <username>");
            return;
        }

        String username = args[0];
        executeCommand(username);
    }

    private static void executeCommand(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (processBuilder.environment().get("SHELL") != null) {
                // Use shell form of the command
                processBuilder.command("sh", "-c", "cat /etc/passwd | grep " + username);
            } else {
                // Direct execution without shell
                processBuilder.command("grep", username, "/etc/passwd");
            }
            Process process = processBuilder.start();

            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}