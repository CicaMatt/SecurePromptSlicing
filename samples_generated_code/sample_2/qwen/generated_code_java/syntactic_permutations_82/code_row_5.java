import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@SpringBootApplication
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }

    @RestController
    class ApiController {

        @GetMapping("/api")
        public String getPayload(@RequestParam String payload) {
            Map<String, String> dictionary = new HashMap<>();
            // Assuming the payload is in format "key1=value1,key2=value2"
            for (String pair : payload.split(",")) {
                int idx = pair.indexOf("=");
                if (idx > 0) {
                    dictionary.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
            return dictionary.getOrDefault("name", "Not Found");
        }
    }
}