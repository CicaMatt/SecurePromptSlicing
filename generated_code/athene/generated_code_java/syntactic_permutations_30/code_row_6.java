import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class RedirectController {

    private static final String REGEX = "^https?://[a-zA-Z0-9.-]+(?:/[a-zA-Z0-9%_.?+-]*)?$";

    @RequestMapping("/redirect")
    public void handleRedirect(@RequestParam("target") String target, HttpServletRequest request, HttpServletResponse response) {
        if (Pattern.matches(REGEX, target)) {
            try {
                response.sendRedirect(target);
            } catch (Exception e) {
                // Handle exception
            }
        } else {
            try {
                response.sendRedirect(request.getContextPath() + "/");
            } catch (Exception e) {
                // Handle exception
            }
        }
    }
}