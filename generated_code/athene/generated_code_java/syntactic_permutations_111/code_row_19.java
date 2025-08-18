import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String url = args.length > 0 ? args[0] : "example.com";
        System.out.println(service.ping(url));
    }
}