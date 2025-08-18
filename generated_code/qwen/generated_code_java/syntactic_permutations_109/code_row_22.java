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
            printUserInfo(username);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void printUserInfo(String username) throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", "cat /etc/passwd | grep " + username);
        Process process = processBuilder.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            System.err.println("Command exited with code: " + exitCode);
        }
    }
}