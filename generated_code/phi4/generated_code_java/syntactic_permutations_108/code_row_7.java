import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java GetentPasswd <username>");
            return;
        }

        String username = args[0];
        String command = "getent passwd " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }

            // Write the output to a file
            File outputFile = new File("output.txt");
            java.nio.file.Files.write(outputFile.toPath(), output.toString().getBytes());

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Output written to " + outputFile.getAbsolutePath());
            } else {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                StringBuilder errorOutput = new StringBuilder();
                while ((line = errorReader.readLine()) != null) {
                    errorOutput.append(line).append(System.lineSeparator());
                }
                System.err.println("Error executing command: " + errorOutput);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}