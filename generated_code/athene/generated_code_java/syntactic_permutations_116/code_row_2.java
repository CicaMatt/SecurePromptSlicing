import java.lang.ProcessBuilder;
import java.io.IOException;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        try {
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }
}