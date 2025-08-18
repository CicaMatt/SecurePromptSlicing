import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserIDFetcher {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java UserIDFetcher <username>");
            return;
        }
        
        String username = args[0];
        try {
            Process process = Runtime.getRuntime().exec("id " + username);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error: User not found or command failed.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}