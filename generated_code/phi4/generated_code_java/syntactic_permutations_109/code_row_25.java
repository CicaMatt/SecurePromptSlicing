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
        String userInfo = getUserInfo(username);

        if (userInfo != null) {
            System.out.println(userInfo);
        } else {
            System.out.println("User not found.");
        }
    }

    private static String getUserInfo(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", "cat /etc/passwd | grep "^ + username");
        
        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();

            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0 && output.length() > 0) {
                return output.toString().trim();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        
        return null;
    }
}