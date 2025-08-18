import java.util.Formatter;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("echo Hello, %s!", "World");
        executeCommand(command);
    }

    public static String print(String format, Object... args) {
        Formatter formatter = new Formatter();
        return formatter.format(format, args).toString();
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            System.out.println("Command executed with exit code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}