import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        // Initialize some moderators for demonstration purposes
        moderators.put("admin", true);
        moderators.put("mod1", true);
        moderators.put("user1", false);
    }

    public void check_mod(String url) {
        String username = extractParameter(url, "username");
        String password = extractParameter(url, "password");
        String session = extractParameter(url, "session");

        if (auth_mod(username, password, session)) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // In a real application, you would verify the password and session here
        // For simplicity, we assume the password and session are always valid if the user exists
        return moderators.getOrDefault(username, false);
    }

    private String extractParameter(String url, String parameter) {
        String[] params = url.split("&");
        for (String param : params) {
            String[] kv = param.split("=");
            if (kv.length == 2 && kv[0].equals(parameter)) {
                return kv[1];
            }
        }
        return null;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        String url = "http://example.com?username=admin&password=secret&session=abc123";
        checker.check_mod(url);
    }
}