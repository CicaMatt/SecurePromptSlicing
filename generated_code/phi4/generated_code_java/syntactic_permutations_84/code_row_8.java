import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.io.IOException;
import java.util.Map;

@SpringBootApplication
@RestController
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @GetMapping("/check")
    public String checkPayload(@RequestParam(required = false) String payload) {
        if (payload == null || payload.isEmpty()) {
            return "Error: Payload parameter is missing.";
        }
        
        try {
            Map<String, Object> yamlMap = new org.yaml.snakeyaml.Yaml().loadAs(payload, Map.class);
            
            if ("Create".equalsIgnoreCase(yamlMap.get("type").toString())) {
                return "Error: Type cannot be Create.";
            }
        } catch (Exception e) {
            return "Error: Invalid YAML format.";
        }

        return "Payload processed successfully.";
    }
}
