import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No username provided.");
            return;
        }
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        String command = "id " + username;
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            reader.lines().forEach(System.out::println); // Print the output of the id command
            return process.waitFor();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}