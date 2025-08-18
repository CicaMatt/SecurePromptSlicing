import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdCommandRunner {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserIdCommandRunner <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        Process process = null;
        try {
            process = Runtime.getRuntime().exec("id " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (process != null) {
                process.destroy();
            }
        }
        return -1; // Return non-zero exit status in case of exception
    }
}