import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class PayloadController {

    public static void main(String[] args) {
        SpringApplication.run(PayloadController.class, args);
    }

    @GetMapping("/api")
    public String getPayload(@RequestParam Map<String, String> payload) {
        return payload.getOrDefault("name", "Name not found");
    }
}