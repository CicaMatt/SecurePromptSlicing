import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = print("%s", "ls");
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            processBuilder.inheritIO();
            Process process = processBuilder.start();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}