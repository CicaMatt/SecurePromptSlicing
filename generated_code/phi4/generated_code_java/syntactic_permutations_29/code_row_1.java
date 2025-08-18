import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.HandlerMapping;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import java.util.regex.Pattern;

@SpringBootApplication
public class WebRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(WebRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private final Pattern pattern = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public ModelAndView redirect(@RequestParam String target) {
        if (pattern.matcher(target).matches()) {
            return new ModelAndView("redirect:" + target);
        } else {
            return new ModelAndView("redirect:/");
        }
    }
}