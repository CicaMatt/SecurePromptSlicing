import java.lang.Runtime;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls -l %s", "/tmp");
        executeCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        try {
            Runtime.getRuntime().exec(command);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}