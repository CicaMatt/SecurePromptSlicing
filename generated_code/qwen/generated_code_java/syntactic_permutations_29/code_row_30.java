import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import javax.validation.constraints.Pattern;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam("target") @Pattern(regexp = ".*example\\.com.*", message = "Invalid URL") String target) {
        return new RedirectView(target);
    }
}