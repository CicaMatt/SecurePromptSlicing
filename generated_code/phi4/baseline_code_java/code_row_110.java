import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformationChecker {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInformationChecker <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit Status: " + exitStatus);
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
        } catch (Exception e) {
            e.printStackTrace();
            return 1; // Indicating failure
        }
    }
}