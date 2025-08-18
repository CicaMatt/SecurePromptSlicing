import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory"; // Modify this to your target directory
        executeLsCommand(directory);
        
        String customPath = print("ls -l %s", "/another/path");
        executeLsCommand(customPath);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void executeLsCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        processBuilder.redirectErrorStream(true);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));

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