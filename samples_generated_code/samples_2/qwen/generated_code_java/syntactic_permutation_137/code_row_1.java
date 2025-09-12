import java.util.HashMap;
import java.util.Map;

public class ModeratorCheck {

    public static void main(String[] args) {
        // Simulating URL parameters for demonstration purposes
        String username = "modUser";
        String password = "securePassword123";
        String session = "session123";

        boolean isModerator = check_mod(username, password, session);
        System.out.println("Is the user a moderator? " + isModerator);
    }

    public static boolean check_mod(String username, String password, String session) {
        return auth_mod(username, password, session);
    }

    public static boolean auth_mod(String username, String password, String session) {
        // Simulating a database of moderators
        Map<String, String> moderators = new HashMap<>();
        moderators.put("modUser", "securePassword123");

        // Checking if the provided credentials match any moderator
        return moderators.containsKey(username) && moderators.get(username).equals(password);
    }
}