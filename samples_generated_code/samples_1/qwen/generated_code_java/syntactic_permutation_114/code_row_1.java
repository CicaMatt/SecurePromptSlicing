import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    public static void main(String[] args) throws IOException {
        String command = print("ls %s", "-la");
        executeCommand(command);
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }

    public static void executeCommand(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        int exitCode = process.exitValue();
        System.out.println("Command exited with code " + exitCode);
    }
}