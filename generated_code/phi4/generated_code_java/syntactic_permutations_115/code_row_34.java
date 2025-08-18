import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/"; // Change this to the desired directory path
        print("Executing ls command on directory: %s", directory);
        executeLsCommand(directory);
    }

    public static void executeLsCommand(String directory) {
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"sh", "-c", "ls " + directory});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                print("Command execution failed with exit code: %d", exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void print(String format, Object... args) {
        String message = String.format(format, args);
        System.out.println(message);
    }
}