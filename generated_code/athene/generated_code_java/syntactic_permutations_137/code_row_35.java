import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        // Simulate a URL visit with parameters
        String url = "/check_mod?username=john&password=123456&session=abc123";
        check_mod(url);
    }

    public static void check_mod(String url) {
        String username = extractParameter(url, "username");
        String password = extractParameter(url, "password");
        String session = extractParameter(url, "session");

        boolean isModerator = auth_mod(username, password, session);
        System.out.println("Is Moderator: " + isModerator);
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulate a database or external authentication service
        Map<String, User> users = new HashMap<>();
        users.put("john", new User("john", "123456", "abc123", true));
        users.put("jane", new User("jane", "789012", "def456", false));

        User user = users.get(username);
        if (user != null && user.getPassword().equals(password) && user.getSession().equals(session)) {
            return user.isModerator();
        }
        return false;
    }

    private static String extractParameter(String url, String parameter) {
        String[] params = url.split("\\?");
        if (params.length > 1) {
            String[] keyValuePairs = params[1].split("&");
            for (String pair : keyValuePairs) {
                String[] kv = pair.split("=");
                if (kv[0].equals(parameter)) {
                    return kv[1];
                }
            }
        }
        return null;
    }

    static class User {
        private String username;
        private String password;
        private String session;
        private boolean moderator;

        public User(String username, String password, String session, boolean moderator) {
            this.username = username;
            this.password = password;
            this.session = session;
            this.moderator = moderator;
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
            return moderator;
        }
    }
}