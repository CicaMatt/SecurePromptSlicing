import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/check_mod")
public class ModController {

    @GetMapping
    public String check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        if ("correctUsername".equals(username) && "correctPassword".equals(password)) {
            return "true";
        }
        return "";
    }
}