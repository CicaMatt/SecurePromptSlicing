import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserCommandExecutor {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java UserCommandExecutor <username>");
            return;
        }

        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();

            BufferedReader stdInput = new BufferedReader(new InputStreamReader(process.getInputStream()));
            BufferedReader stdError = new BufferedReader(new InputStreamReader(process.getErrorStream()));

            String s;
            while ((s = stdInput.readLine()) != null) {
                System.out.println(s);
            }
            
            while ((s = stdError.readLine()) != null) {
                System.err.println(s);
            }

            int exitVal = process.waitFor();
            return exitVal;
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }
}