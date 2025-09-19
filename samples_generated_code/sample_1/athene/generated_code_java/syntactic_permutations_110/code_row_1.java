import java.io.BufferedReader;
import java.io.InputStreamReader;

public class CommandRunner {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java CommandRunner <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec(new String[]{"id", username});
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}