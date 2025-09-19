import java.io.*;

public class GetUserInfo {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java GetUserInfo <username>");
            return;
        }

        String username = args[0];
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        // Add the command and arguments
        processBuilder.command("sh", "-c", "getent passwd " + username);
        
        try {
            Process process = processBuilder.start();

            // Capture the output of the command
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine();
            }

            writer.close();
            reader.close();

            // Wait for the process to complete
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("The command failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}