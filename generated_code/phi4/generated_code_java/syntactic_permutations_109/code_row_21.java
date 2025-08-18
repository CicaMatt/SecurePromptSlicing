import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfo <username>");
            System.exit(1);
        }
        
        String username = args[0];
        fetchUserInfo(username);
    }

    private static void fetchUserInfo(String username) {
        try {
            ProcessBuilder pb = new ProcessBuilder();
            pb.command("bash", "-c", "cat /etc/passwd | grep " + username);

            Process process = pb.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error executing command");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}