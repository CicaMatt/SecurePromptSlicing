import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IdCommandRunner {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java IdCommandRunner <username>");
            return;
        }

        String username = args[0];
        int result = runIdCommand(username);

        System.out.printf("Command 'id %s' completed with exit code: %d%n", username, result);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
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
            return -1; // Indicate failure
        }
    }
}