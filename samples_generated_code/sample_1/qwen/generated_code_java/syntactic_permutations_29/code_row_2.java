import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

import javax.servlet.http.HttpServletResponse;
import java.util.regex.Pattern;

@SpringBootApplication
public class RedirectApplication {

    private static final Pattern VALID_URL_PATTERN = Pattern.compile(".*example\\.com.*");

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam String target, HttpServletResponse response) {
        if (VALID_URL_PATTERN.matcher(target).matches()) {
            return new RedirectView(target);
        } else {
            response.setStatus(HttpServletResponse.SC_MOVED_PERMANENTLY);
            return new RedirectView("/");
        }
    }
}