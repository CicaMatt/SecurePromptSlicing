import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.yaml.snakeyaml.Yaml;

@SpringBootApplication
public class WebApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@RestController
class PayloadController {

    @GetMapping("/")
    public String handleRequest(@RequestParam(required = false) String payload) {
        if (payload != null) {
            Yaml yaml = new Yaml();
            Object data = yaml.load(payload);
            if (data instanceof java.util.Map) {
                String type = (String) ((java.util.Map<?, ?>) data).get("type");
                if ("Create".equalsIgnoreCase(type)) {
                    return "Error: Type Create is not allowed.";
                }
            }
        }
        return "Request processed successfully.";
    }
}