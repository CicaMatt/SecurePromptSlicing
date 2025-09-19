import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserLookup {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserLookup <username>");
            return;
        }
        String username = args[0];
        String userInformation = getUserInfo(username);
        System.out.println(userInformation);
    }

    private static String getUserInfo(String username) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return output.toString().trim();
    }
}