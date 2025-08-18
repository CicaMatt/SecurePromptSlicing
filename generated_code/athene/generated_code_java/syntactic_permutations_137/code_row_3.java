import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        // Initialize some moderators for demonstration purposes
        moderators.put("mod1", true);
        moderators.put("mod2", true);
    }

    public boolean auth_mod(String username, String password, String session) {
        // In a real application, you would verify the password and session.
        // Here we just check if the user is in the moderator list.
        return moderators.containsKey(username);
    }

    public void check_mod(String url) {
        // Extracting username, password, and session from URL
        String[] parts = url.split("\\?");
        if (parts.length > 1) {
            String params = parts[1];
            String[] keyValuePairs = params.split("&");
            Map<String, String> paramsMap = new HashMap<>();
            for (String pair : keyValuePairs) {
                String[] entry = pair.split("=");
                if (entry.length == 2) {
                    paramsMap.put(entry[0], entry[1]);
                }
            }

            String username = paramsMap.get("username");
            String password = paramsMap.get("password");
            String session = paramsMap.get("session");

            boolean isMod = auth_mod(username, password, session);
            if (isMod) {
                System.out.println("User is a moderator.");
            } else {
                System.out.println("User is not a moderator.");
            }
        } else {
            System.out.println("Invalid URL parameters.");
        }
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        String url = "http://example.com/check_mod?username=mod1&password=secret&session=abc123";
        checker.check_mod(url);
    }
}