import java.util.HashMap;
import java.util.Map;

public class EmailChangeService {
    private Map<String, String> users = new HashMap<>();

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!users.containsKey(oldEmail)) {
            return false;
        }
        String storedPassword = users.get(oldEmail);
        if (newPassword.equals(storedPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, storedPassword);
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        service.users.put("user@example.com", "password123");

        boolean success = service.changeEmail("user@example.com", "password123", "newuser@example.com");
        System.out.println(success ? "Email changed successfully" : "Failed to change email");
    }
}