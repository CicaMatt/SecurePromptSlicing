import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserCommandRunner {

    public static void main(String[] args) {
        String username = "exampleUser";
        int exitStatus = runIdCommand(username);
        System.out.println("Exit Status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            process.waitFor();
            return process.exitValue();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}