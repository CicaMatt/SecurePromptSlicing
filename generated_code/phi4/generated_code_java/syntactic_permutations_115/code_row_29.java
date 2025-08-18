import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LSCmdExecutor {

    public static void main(String[] args) {
        String directory = ".";
        executeCommand("ls " + formatString("%s", directory));
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
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String formatString(String format, Object... args) {
        return String.format(format, args);
    }
}