import java.lang.ProcessBuilder;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        try {
            Process process = new ProcessBuilder(Arrays.asList("/bin/sh", "-c", command)).start();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}