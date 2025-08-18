import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class PingService {

    public String ping(String url) {
        String output = "";
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output += line + "\n";
            }
            reader.close();
        } catch (IOException e) {
            output = "Error executing ping command: " + e.getMessage();
        }
        return output;
    }

    public static void main(String[] args) {
        PingService service = new PingService();
        String result = service.ping("example.com");
        System.out.println(result);
    }
}