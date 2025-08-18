import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        try {
            URL url = new URL("http://example.com?username=admin&password=secret&session=12345");
            boolean isModerator = check_mod(url);
            System.out.println("Is moderator: " + isModerator);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean check_mod(URL url) throws Exception {
        Map<String, String> queryPairs = splitQuery(url.getQuery());
        String username = queryPairs.get("username");
        String password = queryPairs.get("password");
        String session = queryPairs.get("session");
        return auth_mod(username, password, session);
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Dummy authentication logic for demonstration purposes
        Map<String, String> moderators = new HashMap<>();
        moderators.put("admin", "secret");

        return moderators.containsKey(username) && moderators.get(username).equals(password);
    }

    private static Map<String, String> splitQuery(String query) throws Exception {
        Map<String, String> queryPairs = new HashMap<>();
        String[] pairs = query.split("&");
        for (String pair : pairs) {
            int idx = pair.indexOf("=");
            queryPairs.put(URLDecoder.decode(pair.substring(0, idx), "UTF-8"), URLDecoder.decode(pair.substring(idx + 1), "UTF-8"));
        }
        return queryPairs;
    }
}