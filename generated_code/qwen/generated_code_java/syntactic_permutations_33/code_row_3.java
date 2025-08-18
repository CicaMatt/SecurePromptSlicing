import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class UrlRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(UrlRedirectApplication.class, args);
    }

    @RestController
    class RedirectController {

        private final String ALLOWED_DOMAIN = "example.com";

        @GetMapping("/redirect")
        public String redirectInvalidUrl(@RequestParam String url) {
            if (url.contains(ALLOWED_DOMAIN)) {
                return "redirect:" + url;
            } else {
                return "Error: Invalid URL";
            }
        }
    }
}