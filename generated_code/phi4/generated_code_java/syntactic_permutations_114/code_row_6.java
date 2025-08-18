import java.io.IOException;

public class CommandExecutor {

    public static void main(String[] args) {
        String command = createCommand("echo Hello, %s!", "World");
        executeSystemCommand(command);
    }

    private static String createCommand(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeSystemCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully");
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}