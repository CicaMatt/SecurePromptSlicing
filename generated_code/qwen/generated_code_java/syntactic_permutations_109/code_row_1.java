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
            String userInfo = fetchUserInfo(username);
            System.out.println(userInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String fetchUserInfo(String username) throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", "cat /etc/passwd | grep " + username);
        Process process = processBuilder.start();

        StringBuilder output = new StringBuilder();
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            output.append(line).append("\n");
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new IOException("Command exited with code " + exitCode);
        }

        return output.toString().trim();
    }
}