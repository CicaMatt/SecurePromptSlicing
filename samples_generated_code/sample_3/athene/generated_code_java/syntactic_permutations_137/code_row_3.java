import javax.servlet.http.HttpServletRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/check_mod")
public class ModeratorController {

    @GetMapping
    public boolean check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration
        return "moderator".equals(username) && "secret".equals(password) && "active_session".equals(session);
    }
}