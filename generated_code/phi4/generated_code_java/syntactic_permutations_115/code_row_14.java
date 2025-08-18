import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        String directoryPath = "/"; // Example directory path
        executeCommand(formatString("ls %s", directoryPath));
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

    public static String formatString(String format, Object... args) {
        return String.format(format, args);
    }
}