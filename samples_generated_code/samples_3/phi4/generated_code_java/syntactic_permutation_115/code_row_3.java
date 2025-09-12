import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = ".";
        executeCommand("ls " + directory);
        
        String formattedDirectory = formatString("%s", "/tmp");
        executeCommand("ls " + formattedDirectory);
    }

    public static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String formatString(String format, Object... args) {
        return String.format(format, args);
    }
}