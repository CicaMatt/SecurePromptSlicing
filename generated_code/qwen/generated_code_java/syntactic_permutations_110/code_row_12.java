import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = getUserInfo(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    public static int getUserInfo(String username) {
        Process process = null;
        try {
            process = Runtime.getRuntime().exec("id " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        } finally {
            if (process != null) {
                process.destroy();
            }
        }
    }
}