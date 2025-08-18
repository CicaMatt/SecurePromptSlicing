import java.lang.ProcessBuilder;
import java.util.Arrays;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        ProcessBuilder pb = new ProcessBuilder(Arrays.asList("bash", "-c", command));
        try {
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                process.getInputStream().transferTo(System.out);
            } else {
                process.getErrorStream().transferTo(System.err);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}