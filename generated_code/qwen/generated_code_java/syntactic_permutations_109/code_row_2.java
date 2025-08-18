import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }
        
        String username = args[0];
        try {
            String userInfo = executeCommand("cat /etc/passwd | grep " + username);
            System.out.println(userInfo);
        } catch (Exception e) {
            System.err.println("Error executing command: " + e.getMessage());
        }
    }

    public static String executeCommand(String command) throws Exception {
        StringBuilder output = new StringBuilder();
        Process p = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        p.waitFor();
        return output.toString();
    }
}