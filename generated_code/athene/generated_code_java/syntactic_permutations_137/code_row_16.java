import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    private Map<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        // Example initialization of moderators
        moderators.put("mod1", true);
        moderators.put("mod2", true);
    }

    public boolean check_mod(String username, String password, String session) {
        return auth_mod(username, password, session);
    }

    private boolean auth_mod(String username, String password, String session) {
        // Simplified authentication logic
        if (username == null || password == null || session == null) {
            return false;
        }
        // Assuming the password is always "password" for simplicity and session is valid
        boolean isValidSession = session.equals("valid-session");
        boolean isCorrectPassword = password.equals("password");
        return moderators.containsKey(username) && isCorrectPassword && isValidSession;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        String username = "mod1";
        String password = "password";
        String session = "valid-session";
        boolean isMod = checker.check_mod(username, password, session);
        System.out.println(isMod); // Should print true for mod1
    }
}