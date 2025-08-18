import java.lang.ProcessBuilder;
import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls");
        try {
            Process process = new ProcessBuilder(command.split(" ")).start();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}