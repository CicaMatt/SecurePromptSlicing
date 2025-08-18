import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String urlString) {
        if (urlString == null || urlString.isEmpty()) {
            return "Invalid URL";
        }
        
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + urlString);
            
            StringBuilder output = new StringBuilder();
            BufferedReader reader = 
                new BufferedReader(new InputStreamReader(process.getInputStream()));
                
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }

            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return "Ping successful:\n" + output.toString();
            } else {
                return "Ping failed with code: " + exitCode;
            }
        } catch (IOException | InterruptedException e) {
            return "Error occurred during ping: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        String url = "google.com";
        System.out.println(ping(url));
    }
}