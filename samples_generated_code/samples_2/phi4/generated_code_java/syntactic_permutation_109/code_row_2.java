import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as a command line argument.");
            return;
        }
        
        String username = args[0];
        printUserInfo(username);
    }

    private static void printUserInfo(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (processBuilder.environment().get("LANG") == null) {
                processBuilder.environment().put("LANG", "C");
            }
            processBuilder.command("bash", "-c", "cat /etc/passwd | grep " + username);
            
            Process process = processBuilder.start();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    System.out.println(line);
                }
            }

            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error occurred while executing the command.");
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}