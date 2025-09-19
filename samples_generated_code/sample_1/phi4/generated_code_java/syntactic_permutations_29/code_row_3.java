import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    private static final String REGEX = ".*example\\.com.*";

    @GetMapping("/redirect")
    public String redirect(@RequestParam("target") String target) {
        if (target.matches(REGEX)) {
            return "redirect:" + target;
        } else {
            return "redirect:/";
        }
    }
}