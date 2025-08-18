import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandExecutor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserCommandExecutor <username>");
            return;
        }

        String username = args[0];
        ProcessBuilder processBuilder = new ProcessBuilder();
        
        switch (System.getProperty("os.name").toLowerCase()) {
            case "windows":
                processBuilder.command("cmd.exe", "/c", "id", username);
                break;
            default:
                processBuilder.command("sh", "-c", "id", username);
                break;
        }

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitStatus = process.waitFor();
            System.out.println("Exit status: " + exitStatus);
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}