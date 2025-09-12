import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        String command = formatString("ls %s", "your_directory_here");
        executeCommand(command);
    }

    private static String formatString(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        Process process;
        try {
            process = Runtime.getRuntime().exec(new String[]{"sh", "-c", command});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}