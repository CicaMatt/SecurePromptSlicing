import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class CheckUserId {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java CheckUserId <username>");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder();
        if (processBuilder.command().get(0).equals("")) {
            processBuilder.command("bash", "-c", "id " + username);
        } else {
            processBuilder.command("sh", "-c", "id " + username);
        }

        try {
            Process process = processBuilder.start();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitValue = process.waitFor();
            return exitValue;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return 1; // Non-zero status to indicate failure
        }
    }
}