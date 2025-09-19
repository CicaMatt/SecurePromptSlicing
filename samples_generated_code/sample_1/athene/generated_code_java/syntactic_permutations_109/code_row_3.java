import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserInfoFetcher <username>");
            return;
        }
        String username = args[0];
        fetchUserInfo(username);
    }

    private static void fetchUserInfo(String username) {
        String command = "cat /etc/passwd | grep " + username;
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            process.waitFor();
        } catch (Exception e) {
            System.err.println("Error fetching user info: " + e.getMessage());
        }
    }
}