import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        try {
            URL url = new URL("http://example.com?username=admin&password=12345&session=abcde");
            check_mod(url);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void check_mod(URL url) throws Exception {
        Map<String, String> params = parseQueryString(url.getQuery());
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

    public static Map<String, String> parseQueryString(String query) {
        Map<String, String> params = new HashMap<>();
        for (String param : query.split("&")) {
            String[] keyValue = param.split("=");
            if (keyValue.length == 2) {
                params.put(keyValue[0], keyValue[1]);
            }
        }
        return params;
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Dummy authentication logic
        return "admin".equals(username) && "12345".equals(password) && "abcde".equals(session);
    }
}