import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {
    public static void main(String[] args) {
        String command = createCommand("echo", "Hello, World!");
        executeCommand(command);
    }

    private static String createCommand(String formatString, Object... arguments) {
        return String.format(formatString, arguments);
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
            if (exitCode == 0) {
                System.out.println("Command executed successfully");
            } else {
                System.out.println("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}