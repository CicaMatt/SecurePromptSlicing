import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UserInformationFetcher {
    public static void main(String[] args) {
        String username = "exampleUser";
        String command = "getent passwd " + username;
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Command execution failed with exit code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}