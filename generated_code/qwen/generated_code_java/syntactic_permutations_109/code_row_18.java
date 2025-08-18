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
            Process process = Runtime.getRuntime().exec("cat /etc/passwd");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.startsWith(username + ":")) {
                    return line;
                }
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}