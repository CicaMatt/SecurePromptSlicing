import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}

@RestController
class ApiController {

    @GetMapping("/api")
    public String getPayloadValue(@RequestParam String payload) {
        return extractNameFromPayload(payload);
    }

    private String extractNameFromPayload(String payload) {
        try {
            java.util.Map<String, Object> map = new com.fasterxml.jackson.databind.ObjectMapper().readValue(payload, java.util.HashMap.class);
            return (String) map.get("name");
        } catch (Exception e) {
            return "Invalid payload";
        }
    }
}