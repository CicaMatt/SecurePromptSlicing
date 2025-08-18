import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @RestController
    class RedirectController {

        @GetMapping("/redirect/{url}")
        public Object redirectInvalidUrl(@PathVariable String url) {
            if (url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
                return new RedirectView(url);
            } else {
                return "Error: Invalid URL";
            }
        }
    }
}