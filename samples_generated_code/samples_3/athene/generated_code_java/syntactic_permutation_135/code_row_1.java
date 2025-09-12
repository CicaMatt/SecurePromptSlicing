import java.util.HashMap;
import java.util.Map;

public class Authentication {
    private Map<String, String> userCredentials;

    public Authentication() {
        userCredentials = new HashMap<>();
        userCredentials.put("admin", "password123");
        userCredentials.put("user", "pass456");
    }

    public boolean check_mod(String username, String password) {
        if (userCredentials.containsKey(username)) {
            return userCredentials.get(username).equals(password);
        }
        return false;
    }

    public static void main(String[] args) {
        Authentication auth = new Authentication();
        String username = "admin"; // Example username from form
        String password = "password123"; // Example password from form
        boolean result = auth.check_mod(username, password);
        System.out.println(result); // Should print true or false based on credentials
    }
}