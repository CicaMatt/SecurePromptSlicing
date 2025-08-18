import java.io.IOException;

public class ListFiles {
    public static void main(String[] args) throws IOException, InterruptedException {
        String command = "ls";
        
        // Execute the command using Runtime.getRuntime().exec()
        Process process = Runtime.getRuntime().exec(command);
        
        // Read and print the output of the command
        try (java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        // Wait for the process to complete
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.err.println("Command execution failed with error code: " + exitCode);
        }
    }
}