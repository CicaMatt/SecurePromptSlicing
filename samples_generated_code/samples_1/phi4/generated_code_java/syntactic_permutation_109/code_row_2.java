import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }

        String username = args[0];
        fetchUserInfo(username);
    }

    private static void fetchUserInfo(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder();
            if (System.getProperty("os.name").toLowerCase().contains("windows")) {
                processBuilder.command("cmd.exe", "/c", "type \"C:\\Windows\\System32\\etc\\passwd\" | findstr /I \"" + username + "\"");
            } else {
                processBuilder.command("sh", "-c", "cat /etc/passwd | grep -i \"" + username + "\"");
            }
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            boolean userFound = false;

            while ((line = reader.readLine()) != null) {
                if (line.contains(":")) { // Simple check for /etc/passwd format
                    System.out.println(line);
                    userFound = true;
                }
            }

            int exitCode = process.waitFor();
            if (!userFound && exitCode == 0) {
                System.out.println("User not found.");
            } else if (exitCode != 0) {
                BufferedReader errorReader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String errorLine;
                while ((errorLine = errorReader.readLine()) != null) {
                    System.err.println(errorLine);
                }
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}