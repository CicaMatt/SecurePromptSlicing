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
            String result = executeCommand(username);
            if (!result.isEmpty()) {
                System.out.println(result);
            } else {
                System.out.println("User not found.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String executeCommand(String username) throws Exception {
        StringBuilder output = new StringBuilder();
        Process process = Runtime.getRuntime().exec("cat /etc/passwd | grep " + username);
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode == 0) {
            return output.toString().trim();
        } else {
            return "";
        }
    }
}