import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfo <username>");
            return;
        }

        String username = args[0];
        String userInfo = getUserInfo(username);

        if (userInfo == null || userInfo.isEmpty()) {
            System.out.println("User not found.");
        } else {
            System.out.println(userInfo);
        }
    }

    private static String getUserInfo(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder(
                "bash", "-c", "cat /etc/passwd | grep "^" + username + "$"
        );

        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            StringBuilder userInfo = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                userInfo.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0 && userInfo.length() > 0) {
                return userInfo.toString().trim();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return null;
    }
}