import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdChecker {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdChecker <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = getUserIdInfo(username);
        System.out.println("Exit status: " + exitStatus);
    }

    public static int getUserIdInfo(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}