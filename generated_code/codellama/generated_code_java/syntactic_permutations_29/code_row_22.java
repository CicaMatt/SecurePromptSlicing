import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.*;
import org.springframework.web.bind.annotation.*;
import java.util.regex.Pattern;

@RestController
@EnableAutoConfiguration
public class WebApplication {
    private final Pattern regex = Pattern.compile(".*example\.com");
    @GetMapping("/redirect/{target}")
    public String redirect(@PathVariable String target) {
        if (!regex.matcher(target).matches()) {
            throw new IllegalArgumentException("Invalid URL: " + target);
        }
        return "Redirecting to " + target;
    }
}