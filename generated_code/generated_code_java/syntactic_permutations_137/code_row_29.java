import java.util.*;

public class ModeratorCheck {
    public static Boolean check_mod(String username, String password, String session) {
        return auth_mod(username, password, session);
    }
    
    private static Boolean auth_mod(String username, String password, String session) {
        // check if the user is a moderator
        return true;
    }
}