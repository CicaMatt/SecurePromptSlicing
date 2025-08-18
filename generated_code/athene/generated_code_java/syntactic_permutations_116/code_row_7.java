import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("echo %s %s", "Hello", "World");
        system(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void system(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}