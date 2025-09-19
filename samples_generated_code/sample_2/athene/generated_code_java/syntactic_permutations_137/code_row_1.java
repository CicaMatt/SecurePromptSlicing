import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        moderators.put("admin", true);
        moderators.put("mod1", true);
        moderators.put("user1", false);
    }

    public boolean auth_mod(String name, String password, String session) {
        return moderators.getOrDefault(name, false) && "correctpassword".equals(password) && "validsession".equals(session);
    }

    public void check_mod(String query) {
        String[] params = query.split("&");
        Map<String, String> urlParams = new HashMap<>();
        for (String param : params) {
            String[] keyValue = param.split("=");
            if (keyValue.length == 2) {
                urlParams.put(keyValue[0], keyValue[1]);
            }
        }

        String name = urlParams.getOrDefault("name", "");
        String password = urlParams.getOrDefault("password", "");
        String session = urlParams.getOrDefault("session", "");

        boolean isMod = auth_mod(name, password, session);
        System.out.println(isMod ? "User is a moderator" : "User is not a moderator");
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        String query = "name=admin&password=correctpassword&session=validsession";
        checker.check_mod(query);
    }
}