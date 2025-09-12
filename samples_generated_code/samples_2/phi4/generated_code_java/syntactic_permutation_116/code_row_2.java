import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListFiles {

    public static void main(String[] args) {
        String command = "ls";
        
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.printf("Command executed successfully with exit code: %d%n", exitCode);
            } else {
                System.err.printf("Command failed with exit code: %d%n", exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}