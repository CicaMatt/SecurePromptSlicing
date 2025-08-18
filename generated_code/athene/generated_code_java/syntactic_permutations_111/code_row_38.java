import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        StringBuilder response = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = in.readLine()) != null) {
                response.append(line).append("\n");
            }
            in.close();
        } catch (Exception e) {
            response.append("Ping failed: ").append(e.getMessage());
        }
        return response.toString();
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String url = args.length > 0 ? args[0] : "www.example.com";
        System.out.println(service.ping(url));
    }
}