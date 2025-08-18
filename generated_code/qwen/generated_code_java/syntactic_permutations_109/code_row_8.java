import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }
        
        String username = args[0];
        try {
            String userInfo = executeCommand("cat /etc/passwd | grep " + username);
            if (!userInfo.isEmpty()) {
                System.out.println(userInfo);
            } else {
                System.out.println("User not found.");
            }
        } catch (Exception e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static String executeCommand(String command) throws Exception {
        StringBuilder output = new StringBuilder();
        Process process = Runtime.getRuntime().exec(command);
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Command execution failed with exit code " + exitCode);
        }
        
        return output.toString().trim();
    }
}