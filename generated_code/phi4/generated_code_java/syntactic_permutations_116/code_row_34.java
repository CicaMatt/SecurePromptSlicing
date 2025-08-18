import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListDirectory {

    public static void main(String[] args) {
        String command = "ls";
        Process process = null;

        try {
            // Execute the 'ls' command and capture the output.
            process = Runtime.getRuntime().exec(command);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Command executed successfully.");
            } else {
                System.err.println("Command execution failed with error code: " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        } finally {
            if (process != null) {
                process.destroy();
            }
        }
    }
}