import java.lang.ProcessBuilder;
import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls");
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Failed to execute command.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}