import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String directory = "/"; // Example directory, change as needed
        executeCommand(lsCommand(directory));
    }

    private static String lsCommand(String dir) {
        return String.format("ls %s", dir);
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
                System.err.format("Command failed with exit code %d%n", exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}