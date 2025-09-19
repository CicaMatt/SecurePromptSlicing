import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @RequestMapping(value = "/ping/{url}", method = RequestMethod.GET)
    public String ping(org.springframework.web.bind.annotation.PathVariable("url") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
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
        // For testing purposes
        PingService service = new PingService();
        System.out.println(service.ping("google.com"));
    }
}
