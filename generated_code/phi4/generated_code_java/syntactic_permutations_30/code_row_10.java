import java.net.URI;
import java.net.URISyntaxException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class RedirectController {

    @GetMapping("/redirect")
    public String handleRedirect(@RequestParam("target") String target, HttpServletRequest request) throws URISyntaxException {
        if (isValidTarget(target)) {
            return "redirect:" + target;
        } else {
            URI uri = new URI(request.getRequestURL().toString());
            return "redirect:" + uri.getScheme() + "://" + uri.getHost();
        }
    }

    private boolean isValidTarget(String target) {
        String regex = "^[a-zA-Z0-9]+$";
        return target.matches(regex);
    }
}
