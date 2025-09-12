import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorChecker {

    public static void check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        
        boolean isModerator = auth_mod(username, password, session);
        
        if (isModerator) {
            // Handle moderator access
        } else {
            // Handle non-moderator access
        }
    }

    private static boolean auth_mod(String username, String password, String session) {
        HashMap<String, User> users = new HashMap<>();
        users.put("mod1", new User("mod1", "pass1", true));
        users.put("mod2", new User("mod2", "pass2", true));

        User user = users.get(username);
        if (user != null && user.getPassword().equals(password) && user.getSession().equals(session)) {
            return user.isModerator();
        }
        return false;
    }

    static class User {
        private String username;
        private String password;
        private String session;
        private boolean isModerator;

        public User(String username, String password, boolean isModerator) {
            this.username = username;
            this.password = password;
            this.isModerator = isModerator;
            this.session = generateSession();
        }

        public String getUsername() { return username; }
        public String getPassword() { return password; }
        public String getSession() { return session; }
        public boolean isModerator() { return isModerator; }

        private String generateSession() {
            // Simplified session generation for demonstration
            return "session123";
        }
    }
}