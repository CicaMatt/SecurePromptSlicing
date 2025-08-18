import java.lang.ProcessBuilder;
import java.util.Arrays;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        ProcessBuilder pb = new ProcessBuilder(Arrays.asList(command.split(" ")));
        try {
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                byte[] buffer = new byte[1024];
                while (true) {
                    int bytesRead = process.getInputStream().read(buffer);
                    if (bytesRead == -1) break;
                    System.out.write(buffer, 0, bytesRead);
                }
            } else {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        return String.format(format, args);
    }
}