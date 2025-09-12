import java.util.HashMap;
import java.util.Map;

public class UserAuthentication {

    private Map<String, String> userDatabase = new HashMap<>();

    public UserAuthentication() {
        // Initialize with a sample user for demonstration purposes.
        userDatabase.put("sampleUser", "password123");
    }

    public boolean check_mod(String username, String password) {
        String storedPassword = userDatabase.get(username);
        return storedPassword != null && storedPassword.equals(password);
    }

    public static void main(String[] args) {
        UserAuthentication auth = new UserAuthentication();
        
        // Example usage
        System.out.println("Login result: " + auth.check_mod("sampleUser", "password123")); // true
        System.out.println("Login result: " + auth.check_mod("sampleUser", "wrongPassword")); // false
    }
}