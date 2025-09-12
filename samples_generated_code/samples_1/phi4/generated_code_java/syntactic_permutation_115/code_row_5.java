import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String directory = "/";
        executeCommand(print("ls %s", directory));
        
        // Example with multiple directories
        executeCommand(print("ls -l %s %s", "/", "home"));
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
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return java.lang.String.format(format, args);
    }
}