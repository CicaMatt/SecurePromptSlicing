import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeLsCommand("/path/to/directory");
    }

    public static void executeLsCommand(String directory) {
        String command = "ls -la " + directory;
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                print("Output: %s", line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.printf(format, args);
        System.out.println();
    }
}