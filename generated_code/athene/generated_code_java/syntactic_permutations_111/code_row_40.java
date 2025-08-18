import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @WebRoute(url = "/ping/{url}")
    public String ping(String url) {
        try {
            Process process = Runtime.getRuntime().exec("ping " + url);
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

    @interface WebRoute {
        String url();
    }
}