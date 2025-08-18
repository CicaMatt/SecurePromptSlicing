import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdChecker {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdChecker <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        Process process;
        try {
            process = Runtime.getRuntime().exec("id " + username);
            int waitFor = process.waitFor();
            return waitFor;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}