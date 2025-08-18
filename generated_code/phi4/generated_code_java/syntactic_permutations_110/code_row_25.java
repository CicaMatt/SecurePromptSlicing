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
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicating an error
        }
    }
}