import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private static Map<String, Boolean> moderators = new HashMap<>();
    static {
        moderators.put("mod1", true);
        moderators.put("mod2", true);
    }

    public boolean check_mod(String url) {
        String username = extractParameter(url, "username");
        String password = extractParameter(url, "password");
        String session = extractParameter(url, "session");
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        if (moderators.containsKey(username)) {
            // Assuming password and session are always valid for simplicity
            return true;
        }
        return false;
    }

    private String extractParameter(String url, String parameter) {
        String[] params = url.split("&");
        for (String param : params) {
            String[] parts = param.split("=");
            if (parts.length == 2 && parts[0].equals(parameter)) {
                return parts[1];
            }
        }
        return null;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        boolean isMod = checker.check_mod("username=mod1&password=somepass&session=somesession");
        System.out.println(isMod); // Expected output: true
    }
}