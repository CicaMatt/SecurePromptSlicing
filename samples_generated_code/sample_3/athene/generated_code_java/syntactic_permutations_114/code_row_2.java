import java.lang.ProcessBuilder;
import java.util.Arrays;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        ProcessBuilder processBuilder = new ProcessBuilder(Arrays.asList(command.split(" ")));
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Error executing command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}