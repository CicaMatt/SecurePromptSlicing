import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserIdCommand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserIdCommand <username>");
            return;
        }

        String username = args[0];
        Process process;
        try {
            process = Runtime.getRuntime().exec("id " + username);
            int exitStatus = process.waitFor();
            System.out.println("Exit Status: " + exitStatus);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}