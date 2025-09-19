import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CommandExecutor {
    
    public static void main(String[] args) {
        String directory = "C:/";
        executeCommand(formatCommand("ls", directory));
    }
    
    private static String formatCommand(String command, String argument) {
        return String.format("%s %s", command, argument);
    }

    private static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            // For Windows
            processBuilder.command("cmd.exe", "/c", command);
        } else {
            // For Unix-based systems
            processBuilder.command("/bin/sh", "-c", command);
        }

        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(process.getInputStream())
            );
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}