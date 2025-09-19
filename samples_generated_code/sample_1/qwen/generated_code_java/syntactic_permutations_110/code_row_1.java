import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class RunIdCommand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java RunIdCommand <username>");
            return;
        }
        
        int exitStatus = runCommand(args[0]);
        System.out.println("Exit Status: " + exitStatus);
    }

    public static int runCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            return process.waitFor();
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}