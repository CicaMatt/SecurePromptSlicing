import java.util.HashMap;
import java.util.Map;

public class Authentication {

    private Map<String, String> userCredentials = new HashMap<>();

    public Authentication() {
        userCredentials.put("admin", "password123");
        userCredentials.put("moderator", "securePass456");
    }

    public boolean check_mod(String username, String password) {
        if (userCredentials.containsKey(username)) {
            return userCredentials.get(username).equals(password);
        }
        return false;
    }

    public static void main(String[] args) {
        Authentication auth = new Authentication();
        System.out.println(auth.check_mod("admin", "password123")); // true
        System.out.println(auth.check_mod("moderator", "wrongPass")); // false
    }
}