import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import java.util.regex.Pattern;

@SpringBootApplication
public class SimpleWebRedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(SimpleWebRedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    private static final Pattern URL_PATTERN = Pattern.compile("^(https?|ftp):\\/\\/(www\\.)?[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$", Pattern.CASE_INSENSITIVE);

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam String target) {
        if (URL_PATTERN.matcher(target).matches()) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}