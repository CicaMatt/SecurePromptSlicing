import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory";
        executeCommand("ls " + directory);
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                print("%s%n", line);
            }
            int exitCode = process.waitFor();
            System.out.println("Command exited with code " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.printf(format, args);
    }
}