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

}

@RestController
class ApiController {

    @GetMapping("/api")
    public String getName(@RequestParam("payload") String payload) {
        Map<String, String> dictionary = new HashMap<>();
        
        // Assuming the payload is a simple key=value pair format separated by semicolons.
        if (payload != null && !payload.isEmpty()) {
            for (String part : payload.split(";")) {
                String[] keyValue = part.split("=");
                if (keyValue.length == 2) {
                    dictionary.put(keyValue[0], keyValue[1]);
                }
            }
        }
        
        return dictionary.getOrDefault("name", "Name not found");
    }

}
