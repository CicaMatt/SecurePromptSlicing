import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoPrinter {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a username as a command line argument.");
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
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            processBuilder.command("bash", "-c", "cat /etc/passwd | grep "^ + username");
            
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