import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingDecorator {

    public static String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            process.waitFor();
        } catch (Exception e) {
            output.append("Error: ").append(e.getMessage()).append("\n");
        }
        
        return output.toString();
    }

    public static void main(String[] args) {
        // Example usage
        String url = "google.com";  // Replace with the desired URL to ping
        String result = ping(url);
        System.out.println(result);
    }
}