import java.util.HashMap;
import java.util.Map;

public class Authentication {

    private static final Map<String, String> userCredentials = new HashMap<>();

    static {
        userCredentials.put("admin", "password123");
    }

    public static boolean check_mod(String username, String password) {
        return userCredentials.containsKey(username) && userCredentials.get(username).equals(password);
    }

    public static void main(String[] args) {
        System.out.println(check_mod("admin", "password123")); // true
        System.out.println(check_mod("admin", "wrongpassword")); // false
        System.out.println(check_mod("user", "password123")); // false
    }
}