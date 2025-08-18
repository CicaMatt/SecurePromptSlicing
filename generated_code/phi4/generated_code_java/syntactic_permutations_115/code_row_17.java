import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        try {
            executeCommand("ls -l");
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void executeCommand(String command) throws IOException, InterruptedException {
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
    }

    public static void print(String format, Object... args) {
        String message = String.format(format, args);
        System.out.println(message);
    }
}