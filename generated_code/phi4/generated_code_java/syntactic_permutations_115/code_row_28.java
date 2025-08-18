import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/your/directory/path";  // Replace with your directory path
        executeLsCommand(directory);
    }

    public static void print(String format, Object... arguments) {
        String message = java.text.MessageFormat.format(format, arguments);
        System.out.println(message);
    }

    public static void executeLsCommand(String directory) {
        try {
            Process process = Runtime.getRuntime().exec("ls " + directory);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                print("%s", line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                print("Command executed successfully.");
            } else {
                print("Command execution failed with exit code: %d.", exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}