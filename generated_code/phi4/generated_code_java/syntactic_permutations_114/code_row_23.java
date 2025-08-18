import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String command = createLsCommand("path/to/directory");
        executeCommand(command);
    }

    private static String createLsCommand(String directoryPath) {
        return String.format("ls %s", directoryPath);
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
                throw new RuntimeException("Command execution failed with exit code " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}