import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            reader.close();
        } catch (IOException e) {
            output.append("Error: ").append(e.getMessage());
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String result = service.ping(args.length > 0 ? args[0] : "example.com");
        System.out.println(result);
    }
}