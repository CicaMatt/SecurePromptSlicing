import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class LsCommandExecutor {

    public static void main(String[] args) {
        String directory = "/path/to/directory"; // Replace with your desired path
        String result = executeLs(directory);
        System.out.println(result);
    }

    public static String executeLs(String directory) {
        ProcessBuilder processBuilder = new ProcessBuilder("ls", directory);
        StringBuilder output = new StringBuilder();
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String errorLine;
                StringBuilder errorOutput = new StringBuilder("Error occurred:\n");
                while ((errorLine = errorReader.readLine()) != null) {
                    errorOutput.append(errorLine).append("\n");
                }
                output.insert(0, errorOutput.toString());
            }
        } catch (IOException | InterruptedException e) {
            output.append("Exception: ").append(e.getMessage()).append("\n");
        }
        return output.toString();
    }

    public static String print(String formatString, Object... args) {
        return String.format(formatString, args);
    }
}