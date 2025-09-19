import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCheck {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Please provide a username as a command line argument.");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitValue = process.exitValue();
            return exitValue;

        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Non-zero status on exception
        }
    }
}