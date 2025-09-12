import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        executeCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
        try {
            processBuilder.start().waitFor();
            System.out.println(processBuilder.start().inputStream.lines().collect(Collectors.joining("\n")));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}