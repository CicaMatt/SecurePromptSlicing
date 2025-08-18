import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java UserInfoFetcher <username>");
            System.exit(1);
        }

        String username = args[0];
        fetchUserInfo(username);
    }

    private static void fetchUserInfo(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("cat", "/etc/passwd");
            processBuilder.redirectErrorStream(true);
            Process process = processBuilder.start();
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            boolean foundUser = false;

            while ((line = reader.readLine()) != null) {
                if (line.contains(":") && line.split(":")[0].equals(username)) {
                    System.out.println(line);
                    foundUser = true;
                    break;
                }
            }

            int exitCode = process.waitFor();
            if (exitCode != 0 || !foundUser) {
                System.err.println("Failed to retrieve information for user: " + username);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}