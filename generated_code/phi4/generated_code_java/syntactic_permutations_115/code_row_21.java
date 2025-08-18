import java.io.BufferedReader;
import java.io.InputStreamReader;

public class LsCommandExecutor {
    public static void main(String[] args) {
        String directory = "."; // Default to current directory
        if (args.length > 0) {
            directory = formatString("Directory: %s", args[0]);
        }
        
        try {
            executeLs(directory);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static void executeLs(String path) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            processBuilder.command("cmd.exe", "/c", "dir " + path);
        } else {
            processBuilder.command("sh", "-c", "ls -l " + path);
        }
        
        Process process = processBuilder.start();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Execution of ls command failed with exit code: " + exitCode);
        }
    }

    public static String formatString(String format, Object... args) {
        return String.format(format, args);
    }
}