import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            return output.toString();
        } catch (IOException e) {
            return "Error pinging: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String result = service.ping("example.com");
        System.out.println(result);
    }
}