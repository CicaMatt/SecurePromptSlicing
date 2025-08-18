import java.util.HashMap;
import java.util.Map;

public class Authentication {

    private Map<String, String> userCredentials = new HashMap<>();

    public Authentication() {
        // Predefined credentials for demonstration purposes
        userCredentials.put("admin", "password123");
    }

    public boolean check_mod(String username, String password) {
        String storedPassword = userCredentials.get(username);
        return storedPassword != null && storedPassword.equals(password);
    }

    public static void main(String[] args) {
        Authentication auth = new Authentication();
        
        // Example usage
        System.out.println(auth.check_mod("admin", "password123")); // true
        System.out.println(auth.check_mod("admin", "wrongpassword")); // false
        System.out.println(auth.check_mod("nonexistentuser", "any password")); // false
    }
}