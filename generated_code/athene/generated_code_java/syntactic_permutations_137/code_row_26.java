import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

public class ModeratorCheckController {

    public boolean check_mod(HttpServletRequest request) {
        HttpSession session = request.getSession(false);
        return session != null && auth_mod(session);
    }

    private boolean auth_mod(HttpSession session) {
        return "moderator".equals(session.getAttribute("userRole"));
    }
}