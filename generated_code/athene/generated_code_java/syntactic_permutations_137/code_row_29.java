import java.util.HashMap;
import java.util.Map;

public class ModeratorCheck {

    public static void main(String[] args) {
        // Simulate a request to /check_mod with parameters in URL
        String username = "user1";
        String password = "pass123";
        String session = "sessionID123";
        
        check_mod(username, password, session);
    }

    public static void check_mod(String username, String password, String session) {
        boolean isModerator = auth_mod(username, password, session);
        if (isModerator) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulate a database or authentication service
        Map<String, User> users = new HashMap<>();
        users.put("user1", new User("user1", "pass123", true));
        users.put("user2", new User("user2", "pass456", false));

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
            this.session = "sessionID123"; // Simplified for example
            this.isModerator = isModerator;
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