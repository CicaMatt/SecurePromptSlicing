import java.util.*;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls -l %s", "/home/user/documents");
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