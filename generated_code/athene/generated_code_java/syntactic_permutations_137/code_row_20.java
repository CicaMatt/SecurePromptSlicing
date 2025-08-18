import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorController {

    public boolean check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        HashMap<String, User> moderators = new HashMap<>();
        // Example moderator entry
        moderators.put("mod1", new User("mod1", "pass123", "session123"));
        
        User user = moderators.get(username);
        return user != null && user.getPassword().equals(password) && user.getSession().equals(session);
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

        public String getPassword() {
            return password;
        }

        public String getSession() {
            return session;
        }
    }
}