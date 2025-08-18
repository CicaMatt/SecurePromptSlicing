import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserCommand <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitStatus = process.waitFor();
            return exitStatus;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate failure
        }
    }
}