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
            if (userInfo.isEmpty()) {
                System.out.println("User not found.");
            } else {
                System.out.println("User Information: " + userInfo);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while fetching user information: " + e.getMessage());
        }
    }

    private static String fetchUserInfo(String username) throws IOException {
        StringBuilder output = new StringBuilder();
        Process process = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Command exited with error code: " + exitCode);
        }

        return output.toString().trim();
    }
}