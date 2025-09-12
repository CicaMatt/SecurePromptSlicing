import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }

        String username = args[0];
        String userInfo = executeCommand("cat /etc/passwd | grep " + username);

        if (userInfo == null || userInfo.isEmpty()) {
            System.out.println("User not found.");
        } else {
            System.out.println(userInfo);
        }
    }

    private static String executeCommand(String command) {
        Process process;
        StringBuilder output = new StringBuilder();

        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = 
                    new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0 && !output.toString().trim().isEmpty()) {
                return output.toString().trim();
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return null;
    }
}