import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @RestController
    class ApiController {

        @GetMapping("/api")
        public String getPayload(@RequestParam String payload) {
            Map<String, String> map = new HashMap<>();
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                if (idx > 0) {
                    map.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return map.getOrDefault("name", "Name not found");
        }
    }
}