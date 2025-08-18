import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = "/usr/bin";
        try {
            executeCommand("ls " + directory);
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
            System.err.println("Command failed with exit code: " + exitCode);
        }
    }

    public static void print(String format, Object... args) {
        System.out.printf(format, args);
    }
}