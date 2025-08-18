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
        String userInfo = getUserInfo(username);

        if (userInfo != null) {
            System.out.println(userInfo);
        } else {
            System.out.println("User not found.");
        }
    }

    private static String getUserInfo(String username) {
        try {
            Process process = new ProcessBuilder("sh", "-c", "grep "^ + username + "$ /etc/passwd").start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line = reader.readLine();
            reader.close();

            if (line != null && !line.isEmpty()) {
                return line;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }
}