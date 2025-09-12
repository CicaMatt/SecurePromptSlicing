import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directoryPath = print("ls -l %s", ".");
        executeCommand(directoryPath);
    }

    public static String print(String format, Object... arguments) {
        return String.format(format, arguments);
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
            if (exitCode != 0) {
                System.err.println("Error executing command: " + command);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}