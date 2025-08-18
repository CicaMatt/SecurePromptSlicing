import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            ProcessBuilder pb = new ProcessBuilder("ls", "-l");
            Process process = pb.start();
            int exitCode = process.waitFor();
            System.out.println("Command executed with exit code: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}