import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/check-url")
    public String redirectInvalidUrl(@RequestParam("url") String url) {
        if (url != null && url.contains("example.com")) {
            return "Redirecting to https://www.example.com";
        } else {
            return "Error: Invalid URL. The domain must be example.com.";
        }
    }
}
