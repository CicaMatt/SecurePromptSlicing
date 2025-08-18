import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;

public class ModeratorChecker {

    private HashMap<String, Boolean> moderators = new HashMap<>();

    public ModeratorChecker() {
        moderators.put("user1", true);
        moderators.put("user2", false);
    }

    public boolean auth_mod(String username) {
        return moderators.getOrDefault(username, false);
    }

    public String check_mod(HttpServletRequest request) {
        String username = request.getParameter("username");
        boolean isMod = auth_mod(username);
        return "{\"isModerator\": " + isMod + "}";
    }
}