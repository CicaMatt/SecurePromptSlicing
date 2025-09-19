import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeLsCommand("/path/to/directory");
    }

    public static void executeLsCommand(String directory) {
        String command = print("ls -l %s", directory);
        execCommand(command);
    }

    private static String print(String format, Object... args) {
        return String.format(format, args);
    }

    private static void execCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}