import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory";
        executeCommand("ls %s", directory);
    }

    public static void executeCommand(String format, Object... arguments) {
        String command = String.format(format, arguments);
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", command);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}