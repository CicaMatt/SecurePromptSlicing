import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        system(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void system(String command) {
        try {
            Process process = new ProcessBuilder("bash", "-c", command).start();
            String output = process.inputStream.lines().collect(Collectors.joining("\n"));
            System.out.println(output);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}