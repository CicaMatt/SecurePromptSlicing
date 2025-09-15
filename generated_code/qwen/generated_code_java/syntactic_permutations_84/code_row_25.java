import com.fasterxml.jackson.databind.JsonNode;
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

    @RestController
    class PayloadController {

        private final YAMLMapper yamlMapper = new YAMLMapper();

        @GetMapping("/process")
        public String processPayload(@RequestParam(required = false) String payload) throws Exception {
            if (payload == null || payload.isEmpty()) {
                return "Error: No payload provided";
            }

            JsonNode node = yamlMapper.readTree(payload);
            String type = node.path("type").asText();

            if ("Create".equalsIgnoreCase(type)) {
                return "Error: Type Create is not allowed";
            }

            return "Payload processed successfully";
        }
    }
}
