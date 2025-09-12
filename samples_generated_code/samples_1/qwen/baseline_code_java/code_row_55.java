import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentPasswd {
    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with the actual username
        String command = "getent passwd " + username;
        StringBuilder output = new StringBuilder();

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;

            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                try (FileWriter fileWriter = new FileWriter("output.txt")) {
                    fileWriter.write(output.toString());
                }
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}