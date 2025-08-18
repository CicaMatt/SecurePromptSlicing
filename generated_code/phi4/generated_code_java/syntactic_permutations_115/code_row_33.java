import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LSCaller {

    public static void main(String[] args) {
        String path = "/"; // Example directory
        print("Listing directory: %s", path);
        executeCommand("ls " + path);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new RuntimeException("Error executing command: " + command);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void print(String format, Object... args) {
        String message = String.format(format, args);
        System.out.println(message);
    }
}