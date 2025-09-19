import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/redirect/{url}")
    public RedirectView redirectInvalidUrl(@PathVariable String url) {
        if (isExampleCom(url)) {
            return new RedirectView(url, true);
        } else {
            // If not from example.com, you might want to handle this differently.
            // Here it returns a view named "error" with the message that URL is invalid
            return new RedirectView("redirect:/invalid", true);
        }
    }

    private boolean isExampleCom(String url) {
        return url != null && (url.startsWith("http://example.com") || url.startsWith("https://example.com"));
    }
}