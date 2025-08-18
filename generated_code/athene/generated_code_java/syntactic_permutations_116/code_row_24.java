import java.lang.Runtime;
import java.lang.String;

public class CommandExecutor {
    public static void main(String[] args) {
        try {
            String command = String.format("ls %s", "-l");
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            System.out.println("Command executed with exit code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}