import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = createCommand("ls %s", "-la");
        executeCommand(command);
    }

    public static String createCommand(String format, String... arguments) {
        return String.format(format, (Object[]) arguments);
    }

    public static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", command);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            System.out.println("Exited with code: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}