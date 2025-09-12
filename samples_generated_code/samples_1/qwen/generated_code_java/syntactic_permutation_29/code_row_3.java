import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.regex.Pattern;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    private final Pattern validUrlPattern = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    String redirect(@RequestParam String target) {
        if (validUrlPattern.matcher(target).matches()) {
            return "redirect:" + target;
        } else {
            return "redirect:/";
        }
    }
}