import java.io.BufferedReader;
import java.io.InputStreamReader;

public class UserPasswdInfo {
    public static void main(String[] args) {
        String username = "user1";
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
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}