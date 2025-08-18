import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCommandExecutor {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserCommandExecutor <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status of the command: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        processBuilder.redirectErrorStream(true);

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