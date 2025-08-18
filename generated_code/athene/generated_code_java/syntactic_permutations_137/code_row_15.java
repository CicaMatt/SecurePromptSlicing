import java.util.HashMap;
import java.util.Map;

public class ModeratorCheck {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorCheck() {
        moderators.put("mod1", true);
        moderators.put("mod2", true);
    }

    public boolean check_mod(String username, String password, String session) {
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        if (moderators.containsKey(username)) {
            // In a real application, you would also validate the password and session
            return moderators.get(username);
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorCheck checker = new ModeratorCheck();
        boolean isMod = checker.check_mod("mod1", "password123", "session456");
        System.out.println(isMod); // Should print true if the user is a moderator
    }
}