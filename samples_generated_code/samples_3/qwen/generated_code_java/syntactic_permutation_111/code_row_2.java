import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class PingController {

    @GetMapping("/ping")
    public String ping(@RequestParam(value = "url", defaultValue = "localhost") String url) {
        StringBuilder output = new StringBuilder();
        try {
            Process process = Runtime.getRuntime().exec("ping -c 4 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line).append("\n");
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                output.append("Ping failed with exit code: ").append(exitCode);
            }
        } catch (IOException | InterruptedException e) {
            output.append("Exception occurred while executing ping command: ").append(e.getMessage());
        }
        return output.toString();
    }
}