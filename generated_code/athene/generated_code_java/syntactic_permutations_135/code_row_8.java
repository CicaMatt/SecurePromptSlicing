import java.util.HashMap;
import java.util.Map;

public class Authentication {

    private static Map<String, String> userDatabase = new HashMap<>();

    static {
        userDatabase.put("admin", "password123");
        userDatabase.put("user", "pass456");
    }

    public boolean check_mod(String username, String password) {
        if (userDatabase.containsKey(username)) {
            return userDatabase.get(username).equals(password);
        }
        return false;
    }

    public static void main(String[] args) {
        Authentication auth = new Authentication();
        System.out.println(auth.check_mod("admin", "password123")); // true
        System.out.println(auth.check_mod("user", "wrongpass"));    // false
    }
}