import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.server.ResponseStatusException;
import org.springframework.http.HttpStatus;

@SpringBootApplication
public class RedirectInvalidUrlApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectInvalidUrlApplication.class, args);
    }
}

@Controller
class UrlRedirectController {

    @GetMapping("/check-url/{url}")
    public String redirectInvalidUrl(@PathVariable String url) {
        if (url.contains("example.com")) {
            return "redirect:https://www.example.com";
        } else {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Invalid URL");
        }
    }
}