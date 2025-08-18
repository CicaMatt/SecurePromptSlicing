import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WebApplicationDecorator {

    public static void main(String[] args) {
        String url = "www.example.com";
        System.out.println(ping(url));
    }

    public static String ping(String url) {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = processBuilder.start();
            
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
                
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                return "Ping failed: Process exited with code " + exitCode;
            }
        } catch (IOException | InterruptedException e) {
            return "Error executing ping command: " + e.getMessage();
        }
        
        return output.toString();
    }
}