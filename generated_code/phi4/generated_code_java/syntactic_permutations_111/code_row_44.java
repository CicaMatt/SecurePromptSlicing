import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WebAppPingDecorator {

    public static String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                output.append(line).append(System.lineSeparator());
            }
            
            return output.toString();
        } catch (IOException e) {
            e.printStackTrace();
            return "Error executing ping command.";
        }
    }

    public static void main(String[] args) {
        // Example usage
        String url = "8.8.8.8";  // Replace with the desired URL or IP address.
        System.out.println(ping(url));
    }
}