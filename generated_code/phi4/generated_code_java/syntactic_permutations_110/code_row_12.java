import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        int exitStatus = executeCommand(username);

        System.out.println("Exit status: " + exitStatus);
    }

    private static int executeCommand(String username) {
        try {
            Process process = new ProcessBuilder("id", username).start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitValue = process.waitFor();
            return exitValue;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Non-zero status indicates failure
        }
    }
}