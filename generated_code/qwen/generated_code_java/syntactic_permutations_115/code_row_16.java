import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/"; // Example directory path
        executeLsCommand(directory);
    }

    public static void executeLsCommand(String path) {
        ProcessBuilder processBuilder = new ProcessBuilder("ls", "-l", path);

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                print("{}", line);
            }

            int exitCode = process.waitFor();
            print("Command exited with code {}", exitCode);

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        System.out.format(format, args);
    }
}