import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoFetcher {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfoFetcher <username>");
            System.exit(1);
        }
        
        String username = args[0];
        String userInfo = getUserInfo(username);

        if (userInfo != null) {
            System.out.println(userInfo);
        } else {
            System.out.println("User not found.");
        }
    }

    public static String executeCommand(String command) {
        StringBuilder output = new StringBuilder();
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
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

    public static String getUserInfo(String username) {
        String command = "cat /etc/passwd | grep "^" + username;
        return executeCommand(command);
    }
}