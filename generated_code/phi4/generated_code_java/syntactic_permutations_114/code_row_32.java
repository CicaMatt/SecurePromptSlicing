import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        String directory = ".";
        printAndExecute("ls %s", directory);
    }

    private static void printAndExecute(String format, Object... args) {
        // Create the command to be executed
        String command = java.lang.String.format(format, args);

        // Print the command (optional)
        System.out.println(command);

        try {
            // Execute the system command
            Process process = Runtime.getRuntime().exec(command);
            
            // Read and print the output of the command
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            // Wait for the execution to complete
            process.waitFor();

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}