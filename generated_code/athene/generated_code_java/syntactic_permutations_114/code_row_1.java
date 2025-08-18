import java.lang.ProcessBuilder;
import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        try {
            Process process = new ProcessBuilder("bash", "-c", command).start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Failed to execute command.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}