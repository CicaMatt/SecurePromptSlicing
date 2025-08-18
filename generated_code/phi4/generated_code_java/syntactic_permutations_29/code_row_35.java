import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import java.util.regex.Pattern;

@SpringBootApplication
public class SimpleWebApp {
    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApp.class, args);
    }
}

@Controller
class RedirectController {

    private static final Pattern EXAMPLE_COM_PATTERN = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public RedirectView redirectToTarget(@RequestParam String target) {
        if (EXAMPLE_COM_PATTERN.matcher(target).matches()) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}