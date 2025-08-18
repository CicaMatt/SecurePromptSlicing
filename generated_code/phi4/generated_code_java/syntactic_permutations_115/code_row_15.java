import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void executeCommand(String format, Object... args) throws IOException {
        try {
            String command = String.format(format, args);
            Process process = Runtime.getRuntime().exec(command);

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new IOException("Command execution failed with exit code " + exitCode);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IOException("Command execution was interrupted", e);
        }
    }

    public static void main(String[] args) {
        try {
            executeCommand("ls %s", ".");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}