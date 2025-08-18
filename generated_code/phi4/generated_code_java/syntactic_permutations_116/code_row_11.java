public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directory = ".";
        
        // Create command using printf-style formatting
        String command = String.format("ls %s", directory);
        
        try {
            // Execute system command and capture the output
            Process process = Runtime.getRuntime().exec(command);
            
            // Read and print the output of the command
            java.io.BufferedReader reader =
                new java.io.BufferedReader(new java.io.InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            // Wait for the process to complete
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new RuntimeException("Error executing command, exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}