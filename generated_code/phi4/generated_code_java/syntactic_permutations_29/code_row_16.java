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

    @GetMapping("/redirect")
    public RedirectView redirectToTarget(@RequestParam String target) {
        if (isValid(target)) {
            return new RedirectView("https://" + target);
        } else {
            return new RedirectView("/");
        }
    }

    private boolean isValid(String url) {
        // Basic validation logic to ensure the URL is safe
        return url != null && !url.trim().isEmpty() && url.contains(".");
    }
}
