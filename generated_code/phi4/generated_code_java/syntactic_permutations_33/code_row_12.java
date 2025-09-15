import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL. Only example.com URLs are allowed.";
        }
    }

}
