import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdCommand {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a username as an argument.");
            return;
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);
        System.out.println("Exit status: " + exitStatus);
    }

    public static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);

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