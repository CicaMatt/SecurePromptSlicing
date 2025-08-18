import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        executeCommand("ls", "-l", "/home");
    }

    private static void executeCommand(String command, String... arguments) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            
            // Add the command and arguments to the process builder
            processBuilder.command(command, (Object[]) arguments);
            
            // Start the process
            Process process = processBuilder.start();
            
            // Read the output of the executed command
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            // Wait for the process to complete and check if it exited normally
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}