import java.lang.ProcessBuilder;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ExecuteLsCommand {
    public static void main(String[] args) {
        String directory = "/path/to/directory";
        String command = String.format("ls -l %s", directory);
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.out.println("Failed to execute command.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}