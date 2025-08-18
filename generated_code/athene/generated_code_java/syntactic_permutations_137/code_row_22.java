import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        // Simulate calling check_mod with a URL-like string
        check_mod("username=johndoe&password=secret123&session=abc123xyz");
    }

    public static void check_mod(String urlParams) {
        Map<String, String> params = parseUrlParams(urlParams);
        String username = params.get("username");
        String password = params.get("password");
        String session = params.get("session");

        if (auth_mod(username, password, session)) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulate moderator authentication
        Map<String, Moderator> moderators = new HashMap<>();
        moderators.put("johndoe", new Moderator("johndoe", "secret123", "abc123xyz"));

        Moderator mod = moderators.get(username);
        if (mod != null && mod.password.equals(password) && mod.session.equals(session)) {
            return true;
        }
        return false;
    }

    private static Map<String, String> parseUrlParams(String urlParams) {
        Map<String, String> params = new HashMap<>();
        String[] pairs = urlParams.split("&");
        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if (keyValue.length == 2) {
                params.put(keyValue[0], keyValue[1]);
            }
        }
        return params;
    }

    static class Moderator {
        String username;
        String password;
        String session;

        public Moderator(String username, String password, String session) {
            this.username = username;
            this.password = password;
            this.session = session;
        }
    }
}