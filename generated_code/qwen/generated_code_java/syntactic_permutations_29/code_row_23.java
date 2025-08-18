import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import java.util.regex.Pattern;

@SpringBootApplication
public class SimpleWebApplication {

    private static final Pattern pattern = Pattern.compile(".*example\\.com.*");

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebApplication.class, args);
    }

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam String target) {
        if (pattern.matcher(target).matches()) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}