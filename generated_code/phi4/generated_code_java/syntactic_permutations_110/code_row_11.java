import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CheckUserId {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java CheckUserId <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (System.getProperty("os.name").toLowerCase().contains("win")) {
            // For Windows
            processBuilder.command("cmd.exe", "/c", "id", username);
        } else {
            // For Unix-based systems
            processBuilder.command("sh", "-c", "id " + username);
        }

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}