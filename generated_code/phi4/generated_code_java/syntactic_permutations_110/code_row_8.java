import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status of the command: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            processBuilder.command("cmd.exe", "/c", "id", username);
        } else {
            processBuilder.command("sh", "-c", "id " + username);
        }

        int exitStatus;
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            exitStatus = process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            exitStatus = 1; // Non-zero for failure
        }

        return exitStatus;
    }
}