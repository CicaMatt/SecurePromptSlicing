import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam String target) {
        if (target.matches(".*example\\.com.*")) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}