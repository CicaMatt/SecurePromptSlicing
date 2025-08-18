import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.method.annotation.RedirectingHandlerMapping;

import javax.servlet.http.HttpServletResponse;
import java.util.regex.Pattern;

@SpringBootApplication
public class SimpleRedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(SimpleRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final Pattern pattern = Pattern.compile("^(https?://[^\\s]+)$");

    @GetMapping("/redirect")
    public String redirectToTarget(@RequestParam String target, HttpServletResponse response) throws Exception {
        if (pattern.matcher(target).matches()) {
            return "redirect:" + target;
        } else {
            return "redirect:/";
        }
    }
}