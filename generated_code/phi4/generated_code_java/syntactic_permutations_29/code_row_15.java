import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private static final String EXAMPLE_COM_REGEX = ".*example\\.com.*";

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam("target") String target) {
        if (target.matches(EXAMPLE_COM_REGEX)) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}