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
        try {
            String userInfo = executeCommand("cat /etc/passwd | grep " + username);
            System.out.println(userInfo);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static String executeCommand(String command) throws IOException, InterruptedException {
        Process process = Runtime.getRuntime().exec(command);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder output = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Command failed with exit code: " + exitCode);
        }
        return output.toString().trim();
    }
}