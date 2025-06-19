import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import org.apache.commons.lang3.StringUtils;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.servlet.view.RedirectView;
@Controller
public class RedirectController {
    private static final String DEFAULT_REDIRECT = "/default";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^/redirect/(.*)$");
    @GetMapping("/redirect/{target}")
    public RedirectView redirectToTarget(HttpServletRequest request) {
        String target = request.getParameter("target");
        Matcher matcher = REDIRECT_PATTERN.matcher(target);
        if (matcher.matches()) {
            return new RedirectView(StringUtils.defaultString(matcher.group(1), DEFAULT_REDIRECT));
        } else {
            return new RedirectView(DEFAULT_REDIRECT);
        }
    }
}