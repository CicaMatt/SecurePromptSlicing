import java.lang.ProcessBuilder;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            ProcessBuilder pb = new ProcessBuilder("ls");
            Process process = pb.start();
            int exitCode = process.waitFor();
            System.out.println("Command executed with exit code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}