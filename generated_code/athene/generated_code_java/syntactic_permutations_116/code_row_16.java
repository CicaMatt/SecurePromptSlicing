import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            String command = "ls";
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            System.out.printf("Command executed with exit code: %d%n", exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}