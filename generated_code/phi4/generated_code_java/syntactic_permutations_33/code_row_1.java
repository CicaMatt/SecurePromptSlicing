import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class UrlRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(UrlRedirectApplication.class, args);
    }
}

@RestController
class UrlController {

    @GetMapping("/redirect")
    public ModelAndView redirectInvalidURL(@RequestParam String url) {
        if (url.contains("example.com")) {
            return new ModelAndView("redirect:" + url);
        } else {
            ModelAndView modelAndView = new ModelAndView();
            modelAndView.addObject("error", "The URL does not belong to example.com");
            return modelAndView;
        }
    }
}