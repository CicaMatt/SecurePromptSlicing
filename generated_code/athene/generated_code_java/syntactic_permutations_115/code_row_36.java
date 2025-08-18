import java.io.IOException;
import java.util.stream.Collectors;

public class CommandExecutor {

    public static void main(String[] args) {
        String command = print("ls -l %s", "/path/to/directory");
        executeCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            String output = process.inputStream.lines().collect(Collectors.joining("\n"));
            System.out.println(output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}