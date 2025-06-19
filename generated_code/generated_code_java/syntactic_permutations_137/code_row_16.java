import java.util.*;
import javax.security.*;
public class Main {
    public static boolean check_mod(String username, String password) {
        return auth_mod(username, password);
    }
}
class Auth {
    public static boolean auth_mod(String username, String password, String session) {
        if (session != null) {
            return true;
        } else {
            return false;
        }
    }
}