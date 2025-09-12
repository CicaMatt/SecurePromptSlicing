import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModController {

    @GetMapping("/check_mod")
    public String check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("correctUsername".equals(username) && "correctPassword".equals(password)) {
            return "true";
        } else {
            return "false";
        }
    }
}