import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ExecLSCommand {
    
    public static void main(String[] args) {
        String directory = "/";
        executeCommand(formatCommand("ls %s", directory));
    }

    private static String formatCommand(String format, Object... arguments) {
        return String.format(format, arguments);
    }

    private static void executeCommand(String command) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            processBuilder.command("cmd.exe", "/c", command);
        } else {
            processBuilder.command("/bin/sh", "-c", command);
        }

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error: Command exited with code " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}