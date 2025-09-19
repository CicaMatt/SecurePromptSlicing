import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        
        String username = args[0];
        getUserInfo(username);
    }

    private static void getUserInfo(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", "cat /etc/passwd | grep "^" + username);
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error: Unable to retrieve user information.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}