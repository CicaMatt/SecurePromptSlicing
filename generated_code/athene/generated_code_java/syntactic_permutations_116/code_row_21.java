import java.lang.ProcessBuilder;
import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        ProcessBuilder pb = new ProcessBuilder("/bin/sh", "-c", command);
        try {
            Process process = pb.start();
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