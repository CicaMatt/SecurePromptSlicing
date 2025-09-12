import java.lang.ProcessBuilder;
import java.util.stream.Collectors;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        ProcessBuilder pb = new ProcessBuilder("/bin/sh", "-c", command);
        try {
            Process process = pb.start();
            String output = process.inputStream.lines().collect(Collectors.joining("\n"));
            System.out.println(output);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}