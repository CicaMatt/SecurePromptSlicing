import java.io.IOException;

public class CheckUser {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Username is required.");
            return;
        }
        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            int exitStatus = process.waitFor();
            System.out.println("Exit Status: " + exitStatus);
        } catch (IOException | InterruptedException e) {
            System.out.println("An error occurred while running the command.");
            e.printStackTrace();
        }
    }
}