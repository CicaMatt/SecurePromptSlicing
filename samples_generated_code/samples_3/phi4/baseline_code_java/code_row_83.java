import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ListDirectory {
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
            System.out.printf("Process exited with code: %d%n", exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}