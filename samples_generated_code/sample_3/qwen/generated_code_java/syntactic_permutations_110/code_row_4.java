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
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);

        try {
            Process process = processBuilder.start();
            int exitStatus = process.waitFor();

            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.err.println(line);
            }

            System.out.println("Exit status: " + exitStatus);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}