import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls -l %s", "/tmp");
        executeCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", command);
        try {
            processBuilder.start().getInputStream().transferTo(System.out);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}