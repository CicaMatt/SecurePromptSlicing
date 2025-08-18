import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }

    @GetMapping("/process")
    public String processRequest(@RequestParam(required = false) String payload) {
        if (payload == null || payload.isEmpty()) {
            return "Error: Missing payload parameter.";
        }
        
        try {
            ObjectMapper yamlReader = new ObjectMapper(new YAMLFactory());
            Payload parsedPayload = yamlReader.readValue(payload, Payload.class);

            if ("Create".equalsIgnoreCase(parsedPayload.getType())) {
                return "Error: Type is Create.";
            }

            // Process the payload further as needed
            return "Payload processed successfully.";

        } catch (Exception e) {
            return "Error parsing YAML payload: " + e.getMessage();
        }
    }

    static class Payload {
        private String type;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }
}