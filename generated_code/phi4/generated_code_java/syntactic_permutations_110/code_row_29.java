import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IdCommandExecutor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java IdCommandExecutor <username>");
            return;
        }

        String username = args[0];
        int commandResult = runIdCommand(username);

        System.out.println("The exit code of the command is: " + commandResult);
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
            return -1; // Return non-zero exit code on failure
        }
    }
}