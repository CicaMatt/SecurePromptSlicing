import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInfo {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserInfo <username>");
            return;
        }

        String username = args[0];
        int exitStatus = getIdInfo(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    public static int getIdInfo(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            return process.exitValue();
        } catch (IOException | InterruptedException e) {
            return 1;
        }
    }
}