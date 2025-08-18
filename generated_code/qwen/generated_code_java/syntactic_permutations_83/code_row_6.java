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

    @RestController
    class NameController {

        @PostMapping("/extractName")
        String extractName(@RequestBody Map<String, Object> payload) {
            return (String) payload.getOrDefault("name", "Name field not found");
        }
    }
}