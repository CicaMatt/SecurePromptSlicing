import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInfoFetcher {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: UserInfoFetcher <username>");
            return;
        }
        String username = args[0];
        try {
            String command = "cat /etc/passwd | grep " + username;
            executeCommand(command);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void executeCommand(String command) throws Exception {
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
        Process process = processBuilder.start();
        
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new Exception("Command execution failed with exit code: " + exitCode);
        }
    }
}