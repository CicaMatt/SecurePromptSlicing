import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class IdCommandRunner {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java IdCommandRunner <username>");
            System.exit(1);
        }
        
        String username = args[0];
        int exitStatus = runIdCommand(username);

        if (exitStatus == 0) {
            System.out.println("Command executed successfully.");
        } else {
            System.out.printf("Command failed with exit status: %d%n", exitStatus);
        }
    }

    private static int runIdCommand(String username) {
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
                
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitValue = process.waitFor();
            return exitValue;

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            return -1;
        }
    }
}