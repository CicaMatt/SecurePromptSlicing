import java.util.HashMap;
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
        HashMap<String, User> users = new HashMap<>();
        // Example moderator user
        users.put("moderator", new User("moderator", "password123", "session456"));
        
        User user = users.get(username);
        if (user != null && user.getPassword().equals(password) && user.getSession().equals(session)) {
            return true;
        }
        return false;
    }

    private static class User {
        private String username;
        private String password;
        private String session;

        public User(String username, String password, String session) {
            this.username = username;
            this.password = password;
            this.session = session;
        }

        public String getUsername() { return username; }
        public String getPassword() { return password; }
        public String getSession() { return session; }
    }
}