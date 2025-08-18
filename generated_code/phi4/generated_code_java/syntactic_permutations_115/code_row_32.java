import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteCommand {

    public static void main(String[] args) {
        String formattedString = createFormattedString("Listing directory: %s", "home/user");
        executeCommand(formattedString);
    }

    private static String createFormattedString(String format, Object... arguments) {
        return String.format(format, arguments);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec("sh -c \"" + command + "\"");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String errorLine;
                while ((errorLine = errorReader.readLine()) != null) {
                    System.err.println(errorLine);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}