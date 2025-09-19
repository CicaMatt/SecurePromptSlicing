import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public String ping(String url) {
        ProcessBuilder processBuilder = new ProcessBuilder("ping", "-c", "4", url);
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new IOException("Ping command failed with exit code " + exitCode);
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return output.toString();
    }
    
    public static void main(String[] args) {
        PingDecorator decorator = new PingDecorator();
        String result = decorator.ping("www.google.com");
        System.out.println(result);
    }
}