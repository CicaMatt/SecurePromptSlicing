import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/redirect/{url}")
    public ModelAndView redirectInvalidUrl(@PathVariable String url) {
        if (url != null && url.startsWith("http://example.com") || url.startsWith("https://example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.setViewName("error");
            modelAndView.addObject("message", "Invalid URL. Only URLs from example.com are allowed.");
            return modelAndView;
        }
    }
}
