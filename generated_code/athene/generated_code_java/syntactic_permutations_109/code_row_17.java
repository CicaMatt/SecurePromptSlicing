import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInformation {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserInformation <username>");
            return;
        }
        String username = args[0];
        getUserInfo(username);
    }

    private static void getUserInfo(String username) {
        String command = "cat /etc/passwd | grep " + username;
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}