import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", command);
        try {
            processBuilder.start().getInputStream().lines().forEach(System.out::println);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}