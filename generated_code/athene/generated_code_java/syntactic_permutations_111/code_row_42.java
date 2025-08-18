import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    public static void main(String[] args) {
        String url = "example.com"; // Example URL, this would normally come from the URL parameter
        System.out.println(ping(url));
    }

    @RequestMapping(value = "/ping/{url}", method = RequestMethod.GET)
    public String ping(@PathVariable("url") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        }
        return output.toString();
    }
}