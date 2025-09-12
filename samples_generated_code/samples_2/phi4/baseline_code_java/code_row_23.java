import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListDirectory {
    public static void main(String[] args) {
        try {
            Process process = Runtime.getRuntime().exec("ls");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                System.err.println("Error executing command, exit code: " + exitCode);
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}