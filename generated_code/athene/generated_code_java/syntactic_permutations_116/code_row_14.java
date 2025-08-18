import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class SystemCommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
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