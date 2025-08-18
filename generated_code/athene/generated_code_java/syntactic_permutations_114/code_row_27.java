import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s %s", "-l", "-a");
        ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", command);
        try {
            processBuilder.start().waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}