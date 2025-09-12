import java.io.IOException;

public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = ".";
        try {
            // Using formatted string to create command with optional arguments
            String command = String.format("ls %s", directory);
            System.out.printf("Executing command: %s\n", command);

            // Execute the command using system function
            int result = Runtime.getRuntime().exec(command).waitFor();
            
            if (result == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with exit code " + result);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}