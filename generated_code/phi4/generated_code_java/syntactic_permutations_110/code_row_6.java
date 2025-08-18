import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommand {

    public static void main(String[] args) {
        String username = "yourUsername"; // Replace with desired username

        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);

            int exitCode = process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return exitCode;

        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Return a non-zero value to indicate failure
        }
    }
}