import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String dir = "/path/to/directory";
        executeCommand(format("ls %s", dir));
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String format(String formatString, Object... args) {
        return String.format(formatString, args);
    }
}