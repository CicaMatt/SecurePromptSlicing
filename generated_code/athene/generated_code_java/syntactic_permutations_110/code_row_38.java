import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDChecker {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Username not provided");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        
        if (exitStatus == 0) {
            System.out.println("Command succeeded");
        } else {
            System.out.println("Command failed with status: " + exitStatus);
        }
    }

    private static int runIdCommand(String username) {
        String command = "id " + username;
        ProcessBuilder processBuilder = new ProcessBuilder(command.split(" "));
        
        try {
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