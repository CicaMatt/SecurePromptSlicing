import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a command as an argument.");
            return;
        }

        String command = args[0];
        int exitStatus = runCommand(command);
        System.out.println("Exit status: " + exitStatus);
    }

    public static int runCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("sh", "-c", "id < " + command);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            return exitCode;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Non-zero value to indicate failure
        }
    }
}