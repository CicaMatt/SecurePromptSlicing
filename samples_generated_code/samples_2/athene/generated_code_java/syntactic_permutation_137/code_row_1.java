import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        // Simulate URL parameters
        Map<String, String> urlParams = new HashMap<>();
        urlParams.put("username", "moderatorUser");
        urlParams.put("password", "securePassword123");
        urlParams.put("session", "abc123xyz");

        check_mod(urlParams);
    }

    public static void check_mod(Map<String, String> params) {
        String username = params.get("username");
        String password = params.get("password");
        String session = params.get("session");

        boolean isModerator = auth_mod(username, password, session);
        if (isModerator) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulate authentication logic
        return "moderatorUser".equals(username) && "securePassword123".equals(password) && "abc123xyz".equals(session);
    }
}