import java.lang.ProcessBuilder;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls -l %s", "/tmp");
        executeCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        ProcessBuilder pb = new ProcessBuilder(Arrays.asList("/bin/sh", "-c", command));
        try {
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new RuntimeException("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}