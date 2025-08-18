import java.util.Formatter;

public class CommandExecutor {
    public static void main(String[] args) throws Exception {
        String command = print("echo %s", "Hello, World!");
        Runtime.getRuntime().exec(command);
    }

    public static String print(String format, Object... args) {
        Formatter formatter = new Formatter();
        return formatter.format(format, args).toString();
    }
}