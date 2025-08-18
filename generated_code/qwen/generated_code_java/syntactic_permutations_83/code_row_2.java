import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
public class NameExtractorApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameExtractorApplication.class, args);
    }
}

@RestController
class NameController {

    @PostMapping("/extractName")
    public String extractName(@RequestBody Map<String, Object> payload) {
        if (payload.containsKey("name")) {
            return payload.get("name").toString();
        } else {
            return "Field 'name' not found";
        }
    }
}