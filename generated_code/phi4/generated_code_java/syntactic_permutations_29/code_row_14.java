import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private static final String REDIRECT_REGEX = ".*example\\.com.*";

    @GetMapping("/redirect")
    public ModelAndView redirectToTarget(@RequestParam("target") String target) {
        ModelAndView modelAndView = new ModelAndView();
        if (target.matches(REDIRECT_REGEX)) {
            modelAndView.setViewName("redirect:" + target);
        } else {
            modelAndView.setViewName("forward:/");
        }
        return modelAndView;
    }
}
