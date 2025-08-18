import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdChecker {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdChecker <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status of id command: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (System.getProperty("os.name").toLowerCase().contains("win")) {
                // For Windows
                processBuilder.command("cmd.exe", "/c", "id " + username);
            } else {
                // For Unix/Linux/MacOS
                processBuilder.command("sh", "-c", "id " + username);
            }

            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            return exitCode;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicating an error occurred
        }
    }
}