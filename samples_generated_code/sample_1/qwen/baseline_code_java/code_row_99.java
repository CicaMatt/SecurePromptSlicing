import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdCommandRunner {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdCommandRunner <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        Process process = null;
        try {
            process = new ProcessBuilder("id", username).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            if (process != null) {
                return process.exitValue();
            }
            return -1;
        }
    }
}