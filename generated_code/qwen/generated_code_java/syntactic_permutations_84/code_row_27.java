import com.fasterxml.jackson.dataformat.yaml.YAMLMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class PayloadController {

    private final YAMLMapper yamlMapper = new YAMLMapper();

    @GetMapping("/check")
    public String checkPayload(@RequestParam(required = false) String payload) throws Exception {
        if (payload == null || payload.isEmpty()) {
            return "Error: Missing payload parameter";
        }

        Payload parsedPayload = yamlMapper.readValue(payload, Payload.class);
        if ("Create".equalsIgnoreCase(parsedPayload.getType())) {
            return "Error: Type cannot be Create";
        }

        return "Success: Payload processed";
    }
}

class Payload {
    private String type;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
