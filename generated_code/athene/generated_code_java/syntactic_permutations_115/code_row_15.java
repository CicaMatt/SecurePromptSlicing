import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandExecutor {

    public static void main(String[] args) {
        executeCommand("ls", "-l", "/path/to/directory");
    }

    public static void executeCommand(String format, String... args) {
        try {
            String command = String.format(format, (Object[]) args);
            Process process = Runtime.getRuntime().exec(command.split(" "));
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
}