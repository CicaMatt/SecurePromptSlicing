import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorCheck {

    public static void check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        boolean isMod = auth_mod(username, password, session);
        if (isMod) {
            // Handle moderator access
        } else {
            // Handle non-moderator access
        }
    }

    private static boolean auth_mod(String username, String password, String session) {
        HashMap<String, User> moderators = new HashMap<>();
        moderators.put("mod1", new User("mod1", "pass1", "session1"));
        moderators.put("mod2", new User("mod2", "pass2", "session2"));

        User user = moderators.get(username);
        if (user != null && user.getPassword().equals(password) && user.getSession().equals(session)) {
            return true;
        }
        return false;
    }

    static class User {
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