import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class WebApplication {
    public static void main(String[] args) {
        SpringApplication.run(WebApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final String pattern = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView handleRedirect(@RequestParam("target") String target) {
        if (target.matches(pattern)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}
