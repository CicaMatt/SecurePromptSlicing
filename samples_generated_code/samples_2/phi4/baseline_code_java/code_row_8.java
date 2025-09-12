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
        String userInfo = executeCommand("cat /etc/passwd | grep " + username);

        if (userInfo == null || userInfo.isEmpty()) {
            System.out.println("User not found.");
        } else {
            System.out.println(userInfo);
        }
    }

    private static String executeCommand(String command) {
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
            if (exitCode == 0) {
                return output.toString();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }
}