import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.util.regex.Pattern;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

}

@Controller
class RedirectController {

    private static final Pattern PATTERN = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public String redirect(@RequestParam("target") String target, RedirectAttributes redirectAttributes) {
        if (PATTERN.matcher(target).matches()) {
            return "redirect:" + target;
        } else {
            return "redirect:/";
        }
    }

}