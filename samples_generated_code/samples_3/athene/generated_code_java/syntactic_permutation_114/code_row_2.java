import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        Runtime.getRuntime().exec(command);
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}