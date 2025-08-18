import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    @GetMapping("/redirect")
    public Object redirectInvalidUrl(@RequestParam String url) {
        if (url.contains("example.com")) {
            return new RedirectView(url);
        } else {
            return "Error: URL must contain example.com";
        }
    }
}