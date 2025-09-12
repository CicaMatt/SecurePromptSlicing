import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInformation <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit Status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        try {
            Process process = new ProcessBuilder("id", username).start();
            process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            return process.exitValue();
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
            return -1; // Non-zero value to indicate failure
        }
    }
}