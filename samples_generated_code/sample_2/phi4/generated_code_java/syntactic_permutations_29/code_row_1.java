import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class SimpleRedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(SimpleRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private static final String REDIRECT_URL_REGEX = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView redirectToTarget(@RequestParam("target") String target) {
        if (target.matches(REDIRECT_URL_REGEX)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}