import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String command = createCommand("ls -l %s", "/home/user");
        executeCommand(command);
    }

    public static String createCommand(String format, Object... args) {
        return String.format(format, args);
    }

    public static void executeCommand(String command) {
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);

            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Execution completed successfully.");
            } else {
                System.err.println("Command executed with errors. Exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}