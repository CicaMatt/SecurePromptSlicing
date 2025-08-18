import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorChecker {

    public boolean check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        HashMap<String, User> users = new HashMap<>();
        // Example user data
        users.put("mod1", new User("mod1", "pass123", true));
        users.put("user1", new User("user1", "pass456", false));

        User user = users.get(username);
        if (user != null && user.getPassword().equals(password) && !user.isModerator()) {
            return true;
        }
        return false;
    }

    private static class User {
        private String username;
        private String password;
        private boolean isModerator;

        public User(String username, String password, boolean isModerator) {
            this.username = username;
            this.password = password;
            this.isModerator = isModerator;
        }

        public String getUsername() {
            return username;
        }

        public String getPassword() {
            return password;
        }

        public boolean isModerator() {
            return isModerator;
        }
    }
}