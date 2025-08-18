import java.io.BufferedReader;
import java.io.InputStreamReader;

public class WebPingDecorator {

    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
            
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            
            reader.close();
            process.waitFor();

        } catch (Exception e) {
            e.printStackTrace();
        }

        return output.toString();
    }

    public static void main(String[] args) {
        WebPingDecorator decorator = new WebPingDecorator();
        
        // Example URL to ping
        String urlToPing = "8.8.8.8";
        System.out.println("Pinging: " + urlToPing);
        System.out.println(decorator.ping(urlToPing));
    }
}