import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserLookup {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserLookup <username>");
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