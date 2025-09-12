import java.lang.Runtime;
import java.lang.Process;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        try {
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}