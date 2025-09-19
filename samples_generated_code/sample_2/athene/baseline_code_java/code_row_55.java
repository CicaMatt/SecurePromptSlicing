import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserInformation {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        ProcessBuilder processBuilder = new ProcessBuilder("bash", "-c", command);
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                // Successfully retrieved user information
            } else {
                System.err.println("Failed to execute command");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}