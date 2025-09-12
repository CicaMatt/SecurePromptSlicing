import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDCommand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIDCommand <username>");
            return;
        }
        
        String username = args[0];
        int exitCode = runIdCommand(username);
        System.out.println("Command exited with code: " + exitCode);
    }

    public static int runIdCommand(String username) {
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
            return -1;
        }
    }
}