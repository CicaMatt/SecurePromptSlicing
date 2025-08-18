import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModeratorController {

    @RequestMapping(value = "/check_mod", method = RequestMethod.GET)
    public boolean check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        // Dummy implementation for demonstration
        return "moderator".equals(username) && "securepassword".equals(password) && "validsession".equals(session);
    }
}