import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }
        String username = args[0];
        String userInfo = getUserInfo(username);
        System.out.println(userInfo);
    }

    private static String getUserInfo(String username) {
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"cat", "/etc/passwd"});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.startsWith(username + ":")) {
                    return line;
                }
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "User not found";
    }
}