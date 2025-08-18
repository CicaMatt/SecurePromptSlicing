import java.io.BufferedReader;
import java.io.InputStreamReader;

public class PingService {

    @RequestMapping(value = "/ping/{url}")
    public String ping(org.springframework.web.bind.annotation.PathVariable("url") String url) {
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
            output.append("Error executing ping command: ").append(e.getMessage());
        }
        return output.toString();
    }
}