import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class GetentCommandExecutor {
    public static void main(String[] args) {
        String username = "username"; // Replace with actual username
        String command = "getent passwd " + username;
        Process process;
        try {
            process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}