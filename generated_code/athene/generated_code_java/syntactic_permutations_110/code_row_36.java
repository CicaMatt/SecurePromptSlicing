import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println(exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder("id", username);
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}