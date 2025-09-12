import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", "id " + username);

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            return exitCode;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Non-zero exit status for failure
        }
    }
}