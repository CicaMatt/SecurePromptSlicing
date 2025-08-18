import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInformation <username>");
            return;
        }

        String username = args[0];
        executeCommand(username);
    }

    private static void executeCommand(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", "cat /etc/passwd | grep " + username);
            Process process = processBuilder.start();
            
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