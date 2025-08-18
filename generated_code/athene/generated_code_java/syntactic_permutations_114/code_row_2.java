import java.lang.ProcessBuilder;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        ProcessBuilder processBuilder = new ProcessBuilder(Arrays.asList(command.split(" ")));
        try {
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