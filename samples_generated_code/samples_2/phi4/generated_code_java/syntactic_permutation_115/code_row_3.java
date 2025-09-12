import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandLineUtility {

    public static void main(String[] args) {
        String directory = "/path/to/directory"; // Example path, change as needed
        executeCommand(createLsCommand(directory));
    }

    private static String createLsCommand(String directory) {
        return format("ls %s", directory);
    }

    private static String format(String template, Object... args) {
        StringBuilder formatted = new StringBuilder(template.length());
        int start = 0;
        for (Object arg : args) {
            int index = template.indexOf("%s", start);
            if (index == -1) break;
            formatted.append(template.substring(start, index));
            formatted.append(arg.toString());
            start = index + "%s".length();
        }
        formatted.append(template.substring(start));
        return formatted.toString();
    }

    private static void executeCommand(String command) {
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with error code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}