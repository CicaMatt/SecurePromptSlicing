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
        int exitCode = runIdCommand(username);

        if (exitCode == 0) {
            System.out.println("The command executed successfully.");
        } else {
            System.out.println("The command failed with exit code: " + exitCode);
        }
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
            return 1;
        }
    }
}