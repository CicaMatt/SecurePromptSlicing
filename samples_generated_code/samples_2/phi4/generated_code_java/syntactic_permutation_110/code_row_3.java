import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInformation <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit Status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
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
            return -1;
        }
    }
}