import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.servlet.ModelAndView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

}

class RedirectController {

    @GetMapping("/redirect/{url}")
    public ModelAndView redirectInvalidUrl(@PathVariable String url) {
        if (url.startsWith("https://") || url.startsWith("http://")) {
            if (url.contains("example.com")) {
                return new ModelAndView("redirect:" + url);
            }
        }
        return new ModelAndView("error", "message", "Error: URL is not from example.com");
    }

}
