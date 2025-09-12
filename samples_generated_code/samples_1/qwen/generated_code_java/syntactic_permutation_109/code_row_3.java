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
            String userInfo = executeCommand("cat /etc/passwd | grep " + username);
            if (!userInfo.isEmpty()) {
                System.out.println(userInfo);
            } else {
                System.out.println("User not found.");
            }
        } catch (IOException e) {
            System.err.println("Error executing command: " + e.getMessage());
        }
    }

    private static String executeCommand(String command) throws IOException {
        StringBuilder output = new StringBuilder();
        Process process = Runtime.getRuntime().exec(command);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        }
        return output.toString().trim();
    }
}