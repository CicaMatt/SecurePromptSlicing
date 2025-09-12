import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeCommand("ls -l");
    }

    public static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/bash", "-c", command);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                print("Output: %s%n", line);
            }
            int exitCode = process.waitFor();
            print("Command exited with code %d%n", exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.printf(format, args);
    }
}