import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@SpringBootApplication
public class NameCheckerApplication {

    public static void main(String[] args) {
        SpringApplication.run(NameCheckerApplication.class, args);
    }

    @RestController
    static class NameController {

        @PostMapping("/checkName")
        String checkName(@RequestBody Map<String, Object> payload) {
            if (payload.containsKey("name")) {
                return payload.get("name").toString();
            }
            return "Name field not found";
        }
    }
}