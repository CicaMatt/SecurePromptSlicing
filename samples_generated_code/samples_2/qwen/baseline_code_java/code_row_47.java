import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class RedirectApplication {

    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@RestController
class RedirectController {

    private static final Pattern PATTERN = Pattern.compile(".*example\\.com.*");

    @GetMapping("/redirect")
    public void redirect(@RequestParam String target, HttpServletResponse response) throws Exception {
        if (PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}