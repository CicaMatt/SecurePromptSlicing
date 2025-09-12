import java.lang.ProcessBuilder;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        try {
            Process process = new ProcessBuilder(Arrays.asList(command.split(" "))).start();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }
}