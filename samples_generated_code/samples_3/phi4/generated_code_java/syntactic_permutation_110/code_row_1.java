import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        try {
            Process process = new ProcessBuilder("id", username).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Non-zero exit status to indicate failure
        }
    }
}