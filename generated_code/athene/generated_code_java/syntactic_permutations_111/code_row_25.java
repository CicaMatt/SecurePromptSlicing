import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (Exception e) {
            output.append("Error: ").append(e.getMessage());
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String url = "example.com"; // This would be the URL from the web request
        System.out.println(service.ping(url));
    }
}