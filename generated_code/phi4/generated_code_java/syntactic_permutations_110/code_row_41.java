import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdChecker {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserIdChecker <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.err.println(line); // Print error output to standard error
            }
            return exitCode;
        } catch (Exception e) {
            e.printStackTrace(System.err);
            return -1; // Indicate an error if the process fails
        }
    }
}