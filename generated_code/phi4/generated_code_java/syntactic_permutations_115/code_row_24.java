import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory";
        executeCommand(format("ls %s", directory));
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

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String format(String format, Object... args) {
        return String.format(format, args);
    }
}