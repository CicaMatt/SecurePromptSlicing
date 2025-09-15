import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

import java.util.Map;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class PayloadController {

    @GetMapping("/check")
    public String checkPayload(@RequestParam(required = false) String payload) {
        if (payload == null || payload.isEmpty()) {
            return "Error: No payload parameter found.";
        }

        Yaml yaml = new Yaml();
        Map<String, Object> data;
        try {
            data = yaml.load(payload);
        } catch (Exception e) {
            return "Error: Unable to parse YAML.";
        }

        if ("Create".equalsIgnoreCase((String) data.get("type"))) {
            return "Error: Type 'Create' is not allowed.";
        }

        return "Payload processed successfully.";
    }
}
