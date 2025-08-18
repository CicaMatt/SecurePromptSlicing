import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        String command = createFormattedString("ls %s", "directoryName");
        executeSystemCommand(command);
    }

    private static String createFormattedString(String format, Object... arguments) {
        return String.format(format, arguments);
    }

    private static void executeSystemCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new RuntimeException("Execution of command failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}