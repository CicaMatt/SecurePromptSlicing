import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserInfoFetcher <username>");
            return;
        }
        String username = args[0];
        try {
            fetchAndPrintUserInfo(username);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void fetchAndPrintUserInfo(String username) throws Exception {
        ProcessBuilder pb = new ProcessBuilder("bash", "-c", "cat /etc/passwd | grep " + username);
        Process process = pb.start();

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Command execution failed with exit code " + exitCode);
        }
    }
}