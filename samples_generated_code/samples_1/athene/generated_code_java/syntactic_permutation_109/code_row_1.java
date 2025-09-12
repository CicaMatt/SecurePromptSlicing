import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        String username = args[0];
        getUserInfo(username);
    }

    private static void getUserInfo(String username) {
        try {
            ProcessBuilder pb = new ProcessBuilder("bash", "-c", "cat /etc/passwd | grep " + username);
            Process process = pb.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}