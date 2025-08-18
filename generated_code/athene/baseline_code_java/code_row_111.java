import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @WebMapping("/ping")
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
        } catch (Exception e) {
            output.append("Error: ").append(e.getMessage());
        }
        return output.toString();
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        System.out.println(service.ping("google.com"));
    }
}

interface WebMapping {
    String value();
}