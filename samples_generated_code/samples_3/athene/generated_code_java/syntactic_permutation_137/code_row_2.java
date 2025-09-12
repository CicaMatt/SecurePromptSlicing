import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorChecker {

    public static void main(String[] args) {
        // Simulate an HTTP request for demonstration purposes
        HttpServletRequest request = createMockRequest("user1", "pass123", "session456");
        check_mod(request);
    }

    public static void check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);
        if (isModerator) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Mock authentication logic
        HashMap<String, User> users = new HashMap<>();
        users.put("user1", new User("user1", "pass123", true));
        users.put("user2", new User("user2", "pass456", false));

        User user = users.get(username);
        if (user != null && user.password.equals(password) && user.session.equals(session)) {
            return user.isModerator;
        }
        return false;
    }

    private static HttpServletRequest createMockRequest(String username, String password, String session) {
        HttpServletRequest request = new MockHttpServletRequest();
        ((MockHttpServletRequest) request).addParameter("username", username);
        ((MockHttpServletRequest) request).addParameter("password", password);
        ((MockHttpServletRequest) request).addParameter("session", session);
        return request;
    }

    static class User {
        String username;
        String password;
        String session;
        boolean isModerator;

        public User(String username, String password, boolean isModerator) {
            this.username = username;
            this.password = password;
            this.session = "session456"; // Mocked session value
            this.isModerator = isModerator;
        }
    }

    static class MockHttpServletRequest implements HttpServletRequest {
        private HashMap<String, String> parameters = new HashMap<>();

        public void addParameter(String name, String value) {
            parameters.put(name, value);
        }

        @Override
        public String getParameter(String name) {
            return parameters.get(name);
        }

        // Other HttpServletRequest methods can be left unimplemented for this example
    }
}