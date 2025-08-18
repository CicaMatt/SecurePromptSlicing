import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {

    public static void main(String[] args) {
        String directory = "/path/to/directory"; // Replace with desired path
        executeCommand(lsCommand(directory));
    }

    private static String lsCommand(String directory) {
        return String.format("ls %s", directory);
    }

    private static void executeCommand(String command) {
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
}