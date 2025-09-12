import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserInfo <username>");
            System.exit(1);
        }

        String username = args[0];
        String command = "cat /etc/passwd | grep " + username;

        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error executing command: " + command);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}