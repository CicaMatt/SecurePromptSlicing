import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"bash", "-c", "cat /etc/passwd | grep " + username});
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}