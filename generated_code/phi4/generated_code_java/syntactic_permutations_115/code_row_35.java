import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String command = createLsCommand("C:\\", " -l");
        executeCommand(command);
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
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static String createLsCommand(String directory, String options) {
        return "cmd.exe /c dir " + formatString(" %s%s", directory, options);
    }

    public static String formatString(String format, Object... args) {
        StringBuilder formatted = new StringBuilder(format);
        for (Object arg : args) {
            formatted.append(arg);
        }
        return formatted.toString();
    }
}