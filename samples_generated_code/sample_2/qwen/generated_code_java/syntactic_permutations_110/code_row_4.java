import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIdChecker {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java UserIdChecker <username>");
            return;
        }
        
        String username = args[0];
        ProcessBuilder processBuilder = new ProcessBuilder("id", username);
        
        try {
            Process process = processBuilder.start();
            int exitCode = process.waitFor();
            System.out.println("Exit Status: " + exitCode);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.err.println(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}