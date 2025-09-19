import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: UserInfo <username>");
            return;
        }
        String username = args[0];
        executeCommand("cat /etc/passwd | grep " + username);
    }

    private static void executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}