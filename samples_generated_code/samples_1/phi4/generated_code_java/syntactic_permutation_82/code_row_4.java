import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebAppApplication.class, args);
    }
}

@RestController
class ApiController {

    @GetMapping("/api")
    public String getPayloadValue(@RequestParam(name = "payload") String payload) {
        String[] keyValuePairs = payload.split(",");
        String nameValue = "";

        for (String pair : keyValuePairs) {
            String[] entry = pair.split("=");
            if (entry.length == 2 && "name".equals(entry[0].trim())) {
                nameValue = entry[1];
                break;
            }
        }

        return nameValue;
    }
}
