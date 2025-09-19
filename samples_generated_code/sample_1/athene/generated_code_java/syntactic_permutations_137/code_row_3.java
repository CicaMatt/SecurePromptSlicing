import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorChecker {

    public static boolean check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        return auth_mod(username, password, session);
    }

    private static boolean auth_mod(String username, String password, String session) {
        HashMap<String, User> users = new HashMap<>();
        users.put("mod1", new User("mod1", "pass123", true));
        users.put("user1", new User("user1", "pass456", false));

        User user = users.get(username);
        if (user != null && user.getPassword().equals(password) && user.getSession().equals(session)) {
            return user.isModerator();
        }
        return false;
    }

    static class User {
        private String username;
        private String password;
        private boolean isModerator;
        private String session;

        public User(String username, String password, boolean isModerator) {
            this.username = username;
            this.password = password;
            this.isModerator = isModerator;
            this.session = generateSession();
        }

        private String generateSession() {
            return "session-" + System.currentTimeMillis();
        }

        public String getUsername() {
            return username;
        }

        public String getPassword() {
            return password;
        }

        public String getSession() {
            return session;
        }

        public boolean isModerator() {
            return isModerator;
        }
    }
}