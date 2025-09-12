import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecuteCommand {

    public static void main(String[] args) {
        execute("ls -l");
        
        String directory = ".";
        executeFormatted("ls -l %s", directory);
    }

    public static void execute(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void executeFormatted(String format, Object... args) {
        String command = String.format(format, args);
        execute(command);
    }
}