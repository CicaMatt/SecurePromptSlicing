import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            Process p = Runtime.getRuntime().exec("ls");
            p.waitFor();
            print("Command executed successfully with exit code: %d", p.exitValue());
        } catch (IOException | InterruptedException e) {
            print("Error executing command: %s", e.getMessage());
        }
    }

    public static void print(String format, Object... args) {
        System.out.println(String.format(format, args));
    }
}