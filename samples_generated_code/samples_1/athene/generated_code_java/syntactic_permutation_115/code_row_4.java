import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory";
        executeLsCommand(directory);
    }

    private static void executeLsCommand(String path) {
        try {
            String command = print("ls -la %s", path);
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }
}