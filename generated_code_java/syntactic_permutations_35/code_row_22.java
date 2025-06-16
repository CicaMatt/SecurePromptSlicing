import java.util.*;

    public class Login {
        private HashMap<String, String> credentials;
    
        public Login() {
            credentials = new HashMap<>();
            // Sample data
            credentials.put("abc", "123");
            credentials.put("test", "password");
        }
    
        public boolean login(String username, String password) {
            if (credentials.containsKey(username)) {
                return credentials.get(username).equals(password);
            } else {
                return false;
            }
        }
    }