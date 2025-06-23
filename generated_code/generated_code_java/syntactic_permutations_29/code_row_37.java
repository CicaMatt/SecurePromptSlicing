import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Controller
public class Redirect {
    @GetMapping("/redirect")
    public void redirect(String target, HttpServletResponse response) throws IOException {
        Pattern p = Pattern.compile("^[\\w.-]+$");
        Matcher m = p.matcher(target);
        if (m.find()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}