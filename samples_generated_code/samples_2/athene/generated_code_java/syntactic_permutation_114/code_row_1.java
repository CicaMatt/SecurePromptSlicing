import java.lang.ProcessBuilder;
import java.text.MessageFormat;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("echo {0} {1}", "Hello", "World");
        try {
            ProcessBuilder pb = new ProcessBuilder(command.split(" "));
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Failed to execute command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return MessageFormat.format(format, args);
    }
}