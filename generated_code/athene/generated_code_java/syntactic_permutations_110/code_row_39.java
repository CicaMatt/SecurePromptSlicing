import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDChecker {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserIDChecker <username>");
            return;
        }

        String username = args[0];
        int exitCode = runIdCommand(username);
        System.out.println("Exit Code: " + exitCode);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }
}