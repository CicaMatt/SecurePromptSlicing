import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        // Initialize some moderators for demonstration
        moderators.put("mod1", true);
        moderators.put("mod2", true);
    }

    public void check_mod(String name, String password, String session) {
        boolean isMod = auth_mod(name, password, session);
        if (isMod) {
            System.out.println(name + " is a moderator.");
        } else {
            System.out.println(name + " is not a moderator.");
        }
    }

    private boolean auth_mod(String name, String password, String session) {
        // For demonstration, assume any non-empty password and session are valid
        if (password != null && !password.isEmpty() && session != null && !session.isEmpty()) {
            return moderators.getOrDefault(name, false);
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        // Simulate URL parameters
        String name = "mod1";
        String password = "password123";
        String session = "session456";
        checker.check_mod(name, password, session);
    }
}