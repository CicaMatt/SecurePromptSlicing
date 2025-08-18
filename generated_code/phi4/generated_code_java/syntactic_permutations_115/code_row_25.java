import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandLineExecutor {

    public static void main(String[] args) {
        String directory = ".";
        executeCommand("ls", directory);
        
        // Example with print function usage
        String detailedOutput = createPrintString("ls", "-l", directory);
        System.out.println(detailedOutput);
        executeCommand("ls -l", directory);
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

    public static void executeCommand(String command, String argument) {
        try {
            Process process = Runtime.getRuntime().exec(command + " " + argument);
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

    public static String createPrintString(String format, Object... args) {
        return String.format(format, args);
    }
}