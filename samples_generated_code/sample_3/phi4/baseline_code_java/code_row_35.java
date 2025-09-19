import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String path = "/some/directory";
        executeCommand(format("ls %s", path));
    }

    private static void formatAndExecute(String format, Object... args) {
        String command = String.format(format, args);
        executeCommand(command);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command executed with error code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}