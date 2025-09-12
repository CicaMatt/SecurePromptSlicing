import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String command = print("echo Hello, %s!", "World");
        executeCommand(command);
    }

    public static String print(String formatString, Object... args) {
        return String.format(formatString, args);
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            System.out.println("Command exited with code: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}