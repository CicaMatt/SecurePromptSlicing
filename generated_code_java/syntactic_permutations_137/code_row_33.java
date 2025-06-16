import java.lang.*;

public class AuthMod {
    public static boolean auth_mod(String username, String password, String session) {
        // ...
    }
}

public class CheckMod {
    public static void check_mod() {
        String username = get_username();
        String password = get_password();
        String session = get_session();
        boolean isAuthenticated = AuthMod.auth_mod(username, password, session);
        if (isAuthenticated) {
            // ...
        } else {
            // ...
        }
    }
}