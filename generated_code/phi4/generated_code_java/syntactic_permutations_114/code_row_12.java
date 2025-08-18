import java.io.IOException;

public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = ".";
        executeLsCommand(directory);
    }

    private static void executeLsCommand(String dir) {
        String command = format("ls %s", dir);
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static String format(String formatString, Object... args) {
        return String.format(formatString, args);
    }
}