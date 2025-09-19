import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
public class NameFieldApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameFieldApplication.class, args);
    }

    @RestController
    static class NameController {

        @PostMapping("/checkName")
        String checkName(@RequestBody Map<String, Object> payload) {
            return payload.containsKey("name") ? (String) payload.get("name") : "";
        }
    }
}