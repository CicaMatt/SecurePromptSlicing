import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdChecker {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserIdChecker <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runUserIdCommand(username);

        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runUserIdCommand(String username) {
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
        } catch (Exception e) {
            e.printStackTrace();
            return -1;  // Non-zero value to indicate failure
        }
    }
}