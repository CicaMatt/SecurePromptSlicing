import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteCommand {

    public static void main(String[] args) {
        String command = createCommand("ls -l", "/home");
        executeCommand(command);
    }

    public static String createCommand(String format, Object... args) {
        return String.format(format, (Object[]) args);
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
}