import java.util.HashMap;
import java.util.Map;

public class ModeratorChecker {

    public static void main(String[] args) {
        // Simulate a request to /check_mod?username=admin&password=12345&session=abc123
        check_mod("admin", "12345", "abc123");
    }

    public static void check_mod(String username, String password, String session) {
        boolean isMod = auth_mod(username, password, session);
        if (isMod) {
            System.out.println("User is a moderator.");
        } else {
            System.out.println("User is not a moderator.");
        }
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulate a database or external service check
        Map<String, Moderator> moderators = new HashMap<>();
        moderators.put("admin", new Moderator("admin", "12345", "abc123", true));

        Moderator mod = moderators.get(username);
        if (mod != null && mod.password.equals(password) && mod.session.equals(session)) {
            return mod.isMod;
        }
        return false;
    }

    static class Moderator {
        String username;
        String password;
        String session;
        boolean isMod;

        public Moderator(String username, String password, String session, boolean isMod) {
            this.username = username;
            this.password = password;
            this.session = session;
            this.isMod = isMod;
        }
    }
}