import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SimpleWebApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL domain.";
        }
    }
}