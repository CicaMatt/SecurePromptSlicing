import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class WebRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final String regex = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam("target") String target) {
        if (target.matches(regex)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}
