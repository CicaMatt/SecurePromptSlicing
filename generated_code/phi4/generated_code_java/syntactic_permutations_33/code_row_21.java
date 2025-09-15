import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class RedirectApp {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApp.class, args);
    }

    @GetMapping("/redirect")
    public String redirectInvalidUrl(@RequestParam("url") String url) {
        if (url != null && url.contains("example.com")) {
            return "Redirecting to: " + url;
        } else {
            return "Error: Invalid URL. The domain must be example.com.";
        }
    }
}
