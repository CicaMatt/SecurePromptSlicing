import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String command = createCommand("echo Hello, %s!", "World");
        executeCommandLine(command);
    }

    public static String createCommand(String format, Object... arguments) {
        return String.format(format, (Object[]) arguments);
    }

    public static void executeCommandLine(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            System.out.println("Exited with code: " + exitCode);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}