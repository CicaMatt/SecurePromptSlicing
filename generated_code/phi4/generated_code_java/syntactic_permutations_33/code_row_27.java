import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class SimpleWebApp {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam("url") String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Invalid URL. Please use a domain of example.com.";
        }
    }
}