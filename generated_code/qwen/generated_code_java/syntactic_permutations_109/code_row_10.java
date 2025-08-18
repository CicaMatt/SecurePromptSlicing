import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        String username = args[0];
        try {
            String result = executeCommand("cat /etc/passwd | grep " + username);
            if (!result.isEmpty()) {
                System.out.println("User Information:\n" + result);
            } else {
                System.out.println("No user found with the username: " + username);
            }
        } catch (Exception e) {
            System.err.println("An error occurred while fetching user information.");
            e.printStackTrace();
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
            throw new Exception("Command execution failed with exit code: " + exitCode);
        }
        return output.toString().trim();
    }
}