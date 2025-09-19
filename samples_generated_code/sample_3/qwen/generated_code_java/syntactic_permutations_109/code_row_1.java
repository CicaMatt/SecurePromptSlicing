import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }
        String username = args[0];
        try {
            String userInfo = fetchUserInfo(username);
            if (userInfo != null && !userInfo.isEmpty()) {
                System.out.println(userInfo);
            } else {
                System.out.println("User not found.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static String fetchUserInfo(String username) throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("/bin/sh", "-c", "cat /etc/passwd | grep " + username);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return output.toString().trim();
        } else {
            return "";
        }
    }
}