import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }

        String username = args[0];
        String userInfo = getUserInfo(username);

        if (userInfo == null) {
            System.out.println("User not found.");
        } else {
            System.out.println(userInfo);
        }
    }

    public static String getUserInfo(String username) {
        try {
            Process process = new ProcessBuilder()
                    .command("sh", "-c", "cat /etc/passwd | grep " + username)
                    .start();

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
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}